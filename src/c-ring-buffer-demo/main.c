#include <stdio.h>  // printf()
#include <stdlib.h> // calloc(), size_t
#include <unistd.h> // sleep()

typedef struct {
  unsigned char flooboo[1];
} Job;

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

static Job * _removeFromQueue(Queue *queue) {
  if (queue->bufferStart == queue->bufferNext) {
    fprintf(stderr, "Ring buffer is empty!\n");
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

constexpr size_t CAP = 8;

int main(void) {
  Job *buffer = calloc(CAP, sizeof(Job));
  auto queue = (Queue){
      .cap = CAP,
      .buffer = buffer,
      .bufferStart = buffer + 3,
      .bufferNext = buffer + 1,
  };
  while (1) {
    for (unsigned int i = 0; i < CAP; i++) {
      printf(" %d", i);
    }
    printf("\tlen = %ld\n", _jobQueueLength(&queue));
    for (unsigned int i = 0; i < CAP; i++) {
      if (queue.buffer + i == queue.bufferStart || queue.buffer + i == queue.bufferNext) {
        printf(" ^");
      } else {
        printf("  ");
      }
    }
    printf("\n");
    _removeFromQueue(&queue);
    sleep(1);
  }
}
