#include <stdlib.h> // abort()

#include "editor.h"

//static inline void ignore(void *) {}
#define IGNORE(x) ((void *)(&x))

int main(int argc, char **argv) {
  IGNORE(argc);
  IGNORE(argv);
  Editor e = editor_new();

  if (e.buffer == nullptr) {
    // TODO: do something interesting
    abort();
  }

  return 0;
}
