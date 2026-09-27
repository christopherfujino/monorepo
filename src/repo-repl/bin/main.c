#include <stdio.h>  // fprintf(), STDIN_FILENO
#include <stdlib.h> // exit()
#include <unistd.h> // isatty()

#include "prompt.h"

int main() {
  if (!isatty(STDIN_FILENO)) {
    fprintf(stderr,
            "It makes no sense to invoke repo-repl without an attached TTY\n");
    exit(1);
  }
  prompt();
}
