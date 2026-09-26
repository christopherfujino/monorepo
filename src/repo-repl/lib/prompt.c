#include <stdio.h>

#include "editline.h"

void prompt() {
  char *input = nullptr;
  while ((input = readline("> ")) != nullptr) {
    printf("Got input: \"%s\"\n", input);
  }

  printf("\n");
}
