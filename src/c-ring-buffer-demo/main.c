#include <stdio.h>  // printf()
#include <stdlib.h> // calloc(), size_t
#include <unistd.h> // sleep()

typedef struct {
  unsigned char flooboo[1];
} Job;

/// This structure wastes 1 element of its cap.
///
/// To be more efficient would require an additional flag to distinguish
/// between an empty and a full buffer.
typedef struct {
  Job *buffer;
  Job *bufferStart;
  Job *bufferNext;
  size_t cap;
} Queue;

static size_t _jobQueueLength(Queue *queue) {
  if (queue->bufferStart == queue->bufferNext) {
    return 0;
  }

  if (queue->bufferNext > queue->bufferStart) {
    return queue->bufferNext - queue->bufferStart;
  }

  auto pastEnd = queue->buffer + queue->cap;
  return pastEnd - queue->bufferStart + queue->bufferNext - queue->buffer;
}

Job *queueRemove(Queue *queue) {
  if (queue->bufferStart == queue->bufferNext) {
    fprintf(stderr, "Ring buffer is empty! (%ld)\n", _jobQueueLength(queue));
    return nullptr;
  }
  Job *current = queue->bufferStart;
  Job *nextStart = current + 1;
  if (nextStart >= queue->buffer + queue->cap) {
    nextStart = queue->buffer;
  }
  queue->bufferStart = nextStart;
  return current;
}

int queueAdd(Queue *queue, Job job) {
  if (_jobQueueLength(queue) >= (queue->cap - 1)) {
    fprintf(stderr, "Ring buffer is (almost) full! (%ld)\n",
            _jobQueueLength(queue));
    return -1;
  }
  *queue->bufferNext = job;
  queue->bufferNext += 1;
  if (queue->bufferNext == queue->buffer + queue->cap) {
    queue->bufferNext = queue->buffer;
  }
  return 0;
}

constexpr size_t CAP = 8;

static inline void _debugQueue(Queue *queue) {
  for (unsigned int i = 0; i < CAP; i++) {
    printf(" %d", i);
  }
  printf("\tlen = %ld\n", _jobQueueLength(queue));
  for (unsigned int i = 0; i < CAP; i++) {
    if (queue->buffer + i == queue->bufferStart ||
        queue->buffer + i == queue->bufferNext) {
      printf(" ^");
    } else {
      printf("  ");
    }
  }
  printf("\n");
}

int main(void) {
  Job *buffer = calloc(CAP, sizeof(Job));
  auto queue = (Queue){
      .cap = CAP,
      .buffer = buffer,
      .bufferStart = buffer + 3,
      .bufferNext = buffer + 1,
  };
  while (1) {
    _debugQueue(&queue);
    auto cur = queueRemove(&queue);
    if (cur == nullptr) {
      break;
    }
    sleep(1);
  }

  while (1) {
    _debugQueue(&queue);
    int ret = queueAdd(&queue, (Job){0});
    if (ret < 0) {
      break;
    }
    sleep(1);
  }
}
