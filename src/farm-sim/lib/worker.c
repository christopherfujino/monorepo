#include <assert.h>    // assert()
#include <pthread.h>   // pthread_create()
#include <stdatomic.h> // atomic_int
#include <stdio.h>     // perror()
#include <stdlib.h>    // abort()
#include <string.h>    // memcpy()
#include <unistd.h>    // usleep()

#include "map.h"
#include "raylib.h"
#include "worker.h"

// TODO: implement a way to signal a job is finished
typedef struct _Job {
  JobType type;
  atomic_int status;
  union {
    Image jobLoadMap;
  } result;
} _Job;

struct _Worker {
  pthread_t thread;
  pthread_mutex_t mutex;

  struct {
    /// Measured in Jobs, not bytes.
    size_t cap;
    _Job *buffer;
    _Job *bufferStart;
    _Job *bufferNext;
  } jobQueue;
};

constexpr size_t jobQueueCap = 16;

constexpr void *threadAttributes = nullptr;

static inline void lock(Worker worker) {
  if (pthread_mutex_lock(&worker->mutex) != 0) {
    perror("Failed to call pthread_mutex_lock()");
    abort();
  }
}

static inline void unlock(Worker worker) {
  if (pthread_mutex_unlock(&worker->mutex)) {
    perror("Failed to call pthread_mutex_unlock()");
    abort();
  }
}

JobStatus jobGetStatus(Job job) { return atomic_load(&job->status); }

/// Must be called from within a lock.
static size_t _workerJobQueueLength(Worker worker) {
  assert(worker->jobQueue.buffer != nullptr);
  if (worker->jobQueue.bufferStart == worker->jobQueue.bufferNext) {
    return 0;
  }

  if (worker->jobQueue.bufferNext > worker->jobQueue.bufferStart) {
    return worker->jobQueue.bufferNext - worker->jobQueue.bufferStart;
  }

  auto pastEnd = worker->jobQueue.buffer + worker->jobQueue.cap;
  return pastEnd - worker->jobQueue.bufferStart + worker->jobQueue.bufferNext -
         worker->jobQueue.buffer;
}

/// Returns 0 on success, -1 if the queue was empty.
static int workerJobDequeue(Worker worker, _Job *returnedJob) {
  int retvalue = 0;
  lock(worker);
  do {
    // neat
    auto queue = worker->jobQueue;
    if (queue.bufferStart == queue.bufferNext) {
      fprintf(stderr, "Ring buffer is empty! (%ld)\n",
              _workerJobQueueLength(worker));
      retvalue = -1;
      break;
    }
    memcpy(returnedJob, queue.bufferStart, sizeof(_Job));
    _Job *nextStart = queue.bufferStart + 1;
    if (nextStart >= queue.buffer + queue.cap) {
      nextStart = queue.buffer;
    }
    queue.bufferStart = nextStart;
    retvalue = 0;
  } while (0);
  unlock(worker);

  return retvalue;
}

static void _jobLoadMap(_Job job) {
  Image *image = calloc(1, sizeof(Image));
  image->data = MapData;
  if (image->data == nullptr) {
    atomic_store(&job.status, jobFailed);
    return;
  }
  image->width = MapWidth;
  image->height = MapHeight;
  image->format = MapFormat;
  image->mipmaps = 1;

  atomic_store(&job.status, 1);
  return image;
}

static void *_work(void *voidSelf) {
  Worker self = voidSelf;
  while (1) {
    lock(self);
    size_t queueLength = _workerJobQueueLength(self);
    unlock(self);

    _Job job = {};
    if (queueLength > 0) {
      if (workerJobDequeue(self, &job) < 0) {
        // This should be unreachable due to the previous check
        abort();
      }
      switch (job.type) {
      case jobLoadMap:
        _jobLoadMap();
        break;
      }
    } else {
      // 0.01 seconds
      if (usleep(10'000) < 0) {
        perror("Failed to call usleep()");
        abort();
      }
    }
  }
}

Job workerJobEnqueue(Worker worker, JobType type) {
  _Job *job = nullptr;

  lock(worker);
  do {
    auto queue = worker->jobQueue;
    if (_workerJobQueueLength(worker) >= (queue.cap - 1)) {
      fprintf(stderr, "Ring buffer is (almost) full! (%ld)\n",
              _workerJobQueueLength(worker));
      break;
    }

    job = malloc(sizeof(_Job));
    if (job == nullptr) {
      perror("malloc() failed");
      abort();
    }
    *job = (_Job){
        .type = type,
    };
    atomic_init(&job->status, jobQueued);

    *queue.bufferNext = *job;
    queue.bufferNext += 1;
    if (queue.bufferNext == queue.buffer + queue.cap) {
      queue.bufferNext = queue.buffer;
    }
  } while (0);
  unlock(worker);

  return job;
}

Worker workerSpawn() {
  struct _Worker *worker = calloc(1, sizeof(struct _Worker));
  worker->jobQueue.cap = jobQueueCap;
  worker->jobQueue.buffer = calloc(jobQueueCap, sizeof(_Job));
  worker->jobQueue.bufferStart = worker->jobQueue.buffer;
  worker->jobQueue.bufferNext = worker->jobQueue.buffer;
  pthread_mutex_init(&worker->mutex, nullptr);
  if (pthread_create(&worker->thread, threadAttributes, _work, worker) != 0) {
    perror("pthread_create() failed!");
    abort();
  }

  return worker;
}

void workerDispose(Worker worker) {
  // TODO tear down thread?
  // TODO: clean up mutex?
  free(worker->jobQueue.buffer);
  free(worker);
}
