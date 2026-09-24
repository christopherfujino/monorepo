#include "globals.h"
#include "raylib.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset()
#include <sys/param.h>
#include <time.h> // nanosleep()

static inline void lock(pthread_mutex_t *mutex) {
  if (pthread_mutex_lock(mutex) != 0) {
    perror("Failed to call pthread_mutex_lock()");
    abort();
  }
}

static inline void unlock(pthread_mutex_t *mutex) {
  if (pthread_mutex_unlock(mutex)) {
    perror("Failed to call pthread_mutex_unlock()");
    abort();
  }
}

static const int TRUE = 1;
static const int FALSE = 0;

enum Jobs {
  job_map,

  job_count,
};

typedef struct JobStat {
  bool finished;
  const char *error;
} JobStat;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
JobStat sharedJobStats[job_count];

static void *mapWorker(void *voidIndex) {
  int *index = voidIndex;
  Image map = GenImagePerlinNoise(WORLD_WIDTH, WORLD_HEIGHT, 5, 40, 100);

  if (!ExportImageAsCode(map, "./gen/map_gen.h")) {
    {
      lock(&m);
      sharedJobStats[*index].finished = true;
      sharedJobStats[*index].error = "Failed to export image as code";
      unlock(&m);
    }
    return (void *)(&FALSE);
  }

  UnloadImage(map);

  {
    lock(&m);
    sharedJobStats[*index].finished = true;
    unlock(&m);
  }

  return (void *)(&TRUE);
}

int main() {
  {
    lock(&m);
    memset(&sharedJobStats, 0x0, sizeof(sharedJobStats));
    unlock(&m);
  }
  pthread_t workerThreads[job_count] = {};
  int workerArgs[job_count] = {};
  constexpr void *threadAttributes = nullptr;
  for (int i = 0; i < job_count; i++) {
    workerArgs[i] = i;
    if (pthread_create(workerThreads + i, threadAttributes, mapWorker,
                       workerArgs + i) != 0) {
      perror("pthread_create() failed!");
      abort();
    }
  }

  // 0.0375s
  struct timespec sleepSpec = {
      .tv_sec = 0,
      .tv_nsec = 37'500'000,
  };
  int finishCount = 0;
  size_t animationIndex = 0;
  char buffer[256] = {};
  size_t bufsize = 0;
  while (finishCount < job_count) {
    putchar('\r');
    bufsize = snprintf(buffer, sizeof(buffer), "Executing %d of %d jobs...",
                       job_count - finishCount, job_count);
    if (bufsize < 0) {
      perror("Failed to call snprintf()");
      abort();
    }
    // return value of snprintf() will not be accurate if truncated
    bufsize = MIN(bufsize, sizeof(buffer) - 1);
    animationIndex += 1;
    if (animationIndex == bufsize) {
      animationIndex = 0;
      for (size_t i = 0; i < bufsize; i++) {
        putchar(' ');
      }
      putchar('\r');
    }
    //printf("[DEBUG] %s\n", buffer);
    for (size_t i = 0; i < animationIndex; i++) {
      char c = buffer[i];
      if (c == '\0') {
        break;
      }
      putchar(c);
    }
    if (fflush(stdout) != 0) {
      perror("Failed to call fflush()");
      abort();
    }

    nanosleep(&sleepSpec, nullptr);
    finishCount = 0;
    {
      lock(&m);
      for (size_t i = 0; i < job_count; i++) {
        if (sharedJobStats[i].finished) {
          finishCount++;
        }
      }
      unlock(&m);
    }
  }

  bool allSuccess = true;
  for (size_t i = 0; i < job_count; i++) {
    void *success = nullptr;
    int err = pthread_join(workerThreads[i], &success);
    if (err != 0) {
      perror("pthread_join() failed!");
      abort();
    }
    if (!*((int *)success)) {
      fprintf(stderr, "Job #%ld failed!\n", i);
      allSuccess = false;
    }
  }

  if (allSuccess) {
    printf("Finished %d jobs successfully!\n", job_count);
  } else {
    printf("Finished, but with failures!\n");
  }
}
