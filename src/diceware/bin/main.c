#include <stdio.h> // printf()

#include "chrislib.h"
#include "utils.h"
#include "word.h"

int main(void) {
  // TODO: parameterize
  constexpr unsigned char n = 4;

  Word w = wordNew("");
  for (unsigned char i = 0; i < n; i++) {
    w = wordCat(w, getWord());
  }
  // TODO: consider using `zenity` if no TTY attached
  bool clipboarded = clipboard(w.str);
  char *msg = nullptr;
  resultTry(cSprintf(&msg, "\n%s\n\n", w.str));
  if (clipboarded) {
    resultTry(cSprintf(&msg, "%s\U0001F4CB Copied to X11 clipboard!\n", msg));
  } else {
  }
  zenity(msg);
  printf("%s", msg);
  return 0;
}
