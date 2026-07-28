#include <stdio.h>

#include "editline.h"

int main(void) {
  char *input = NULL;
  while ((input = readline("> ")) != NULL) {
    printf("Got input\n");
  }

  putc('\n', stdout);

  return 0;
}
