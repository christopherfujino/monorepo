#include <stdio.h>  // fread(), popen()
#include <stdlib.h> // system()
#include <string.h> // strcat()

#include "chrislib.h" // vSprintf()
#include "utils.h"

[[nodiscard]]
static bool _sys(const char *name) {
  int result = system(name);
  if (result < 0) {
    perror("system() failed");
    return false;
  }
  return result == 0;
}

bool which(const char *name) {
  constexpr char whichString[] = "which ";
  bool resultBool = false;
  char cmd[256];
  char *buffer = cmd;
  const size_t nameLen = strlen(name);
  if (nameLen > (sizeof(cmd) - sizeof(whichString))) {
    buffer = malloc(nameLen + sizeof(whichString));
  }
  strcpy(buffer, "which ");
  strcat(buffer, name);
  int result = system("which xclip >/dev/null");
  if (result < 0) {
    perror("system() failed");
    resultBool = false;
    goto cleanup;
  }
  resultBool = result == 0;

cleanup:
  if (buffer != cmd) {
    free(buffer);
  }
  return resultBool;
}

bool zenity([[maybe_unused]] const char *msg) {
  int result = which("zenity");
  if (result == false) {
    return false;
  }

  char *cmd = nullptr;
  resultTry(cSprintf(&cmd,
                     "zenity "
                     "--info "
                     "--title=Diceware "
                     "--text='<big><tt>%s</tt></big>'",
                     msg));
  return _sys(cmd);
}

bool clipboard(const char *password) {
  bool result = which("xclip");
  if (!result) {
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

// i3-nagbar -t warning -m 'flooboo' --font 'pango:DejuVu Sans Mono 18'
