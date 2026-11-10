#include <stdio.h>  // fread(), popen()
#include <stdlib.h> // system()

#include "clipboard.h"

[[nodiscard]]
bool clipboard(const char *password) {
  int result = system("which xclip");
  if (result < 0) {
    perror("system() failed");
    return false;
  } else if (result > 0) {
    return false;
  }

  FILE *writer = popen("xclip -selection clipboard", "w");
  fprintf(writer, "%s", password);
  result = fclose(writer);
  if (result != 0) {
    perror("fclose() failed after popen(\"xclip ...\")");
    return false;
  }

  return true;
}
