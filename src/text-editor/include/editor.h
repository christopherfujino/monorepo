#ifndef MONOREPO_SRC_TXT_INCLUDE_EDITOR_H
#define MONOREPO_SRC_TXT_INCLUDE_EDITOR_H

typedef struct Buffer {
  const char *path;
} Buffer;

typedef struct Editor {
  Buffer *buffer;
} Editor;

Editor editor_new(void);

#endif // MONOREPO_SRC_TXT_INCLUDE_EDITOR_H
