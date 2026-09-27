#include <stdio.h>  // printf()
#include <stdlib.h> // free()
#include <string.h> // strdup(), strlen(), strncmp()

#include "common.h"
#include "editline.h"
#include "prompt.h"

/// Attempt to complete the pathname, returning an allocated copy.
///
/// Fill in *unique if we completed it, or set it to 0 if ambiguous.
static char *rl_complete_func(char *token, int *match) {
  int index = 0;
  int matchlen = 0;
  int matchCount = 0;

  for (unsigned int i = 0; i < commandListLength; i++) {
    int partlen = strlen(token); /* Part of token */

    if (strncmp(commandList[i], token, partlen) == 0) {
      index = i;
      matchlen = partlen;
      matchCount++;
    }
  }

  if (matchCount == 1) {
    *match = 1;
    return strdup(commandList[index] + matchlen);
  }

  return nullptr;
}

static int rl_list_possible_func(char *token, char ***av) {
  unsigned int total = 0;
  char **copy;

  copy = malloc(commandListLength * sizeof(char *));
  for (unsigned int i = 0; i < commandListLength; i++) {
    if (!strncmp(commandList[i], token, strlen(token))) {
      copy[total] = strdup(commandList[i]);
      total++;
    }
  }
  *av = copy;

  return total;
}

void prompt() {
  // TODO move to a single init() func
  rl_set_complete_func(&rl_complete_func);
  rl_set_list_possib_func(&rl_list_possible_func);

  char *input = nullptr;
  while ((input = readline("> ")) != nullptr) {
    printf("Got input: \"%s\"\n", input);
    free(input);
  }

  printf("\n");
}
