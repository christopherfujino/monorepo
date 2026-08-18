#ifndef __TXT_EDITOR_H
#define __TXT_EDITOR_H

typedef struct Buffer {
  const char *path;
} Buffer;

typedef struct Editor {
  Buffer *buffer;
} Editor;

Editor editor_new(void);

#endif // __TXT_EDITOR_H
