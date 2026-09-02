#include "buffer.h"

Buffer buffer_new() {
  constexpr size_t INITIAL_CAP = 8;
  return (Buffer){
      .len = 0,
      .cap = INITIAL_CAP,
      .data = malloc(INITIAL_CAP * sizeof(unsigned char)),
  };
}

void buffer_push(Buffer *buffer, unsigned char byte) {
  if (buffer->len == buffer->cap) {
    // grow
    buffer->cap *= 2;
    // if we want to be able to recover, we must assign to a temp
    buffer->data = realloc(buffer->data, buffer->cap);
    if (buffer->data == nullptr) {
      fprintf(stderr, "realloc() failure\n");
      abort();
    }
  }
  buffer->data[buffer->len] = byte;
  buffer->len++;
}

// Warning: re-uses `buffer`'s data buffer.
char *buffer_to_string(Buffer *buffer) {
  char *out = realloc(buffer->data, buffer->len + 1);
  if (out == nullptr) {
    fprintf(stderr, "realloc() failure\n");
    abort();
  }
  out[buffer->len] = '\0';
  // TODO should we zero out `buffer`?

  return out;
}
