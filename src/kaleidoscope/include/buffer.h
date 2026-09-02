#ifndef __src_kaleidoscope_include_buffer_h
#define __src_kaleidoscope_include_buffer_h

#include <stddef.h> // size_t
#include <stdio.h>  // fprintf(), stderr
#include <stdlib.h> // abort(), malloc()

typedef struct Buffer {
  size_t len;
  size_t cap;
  unsigned char *data;
} Buffer;

Buffer buffer_new();

void buffer_push(Buffer *buffer, unsigned char byte);

char *buffer_to_string(Buffer *buffer);

#endif // __src_kaleidoscope_include_buffer_h
