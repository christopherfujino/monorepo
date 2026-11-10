#include <stdio.h>  // printf()
#include <stdlib.h> // rand(), srand()
#include <time.h>   // time()

#include "clipboard.h"
#include "word.h"

int main(void) {
  // TODO: parameterize
  constexpr unsigned char n = 4;
  Word w = wordNew("");
  srand(time(nullptr));
  for (unsigned char i = 0; i < n; i++) {
    w = wordCat(w, getWord());
  }
  bool clipboarded = clipboard(w.str);
  printf("\n%s\n\n", w.str);
  if (clipboarded) {
    printf("Already copied to X11 clipboard!\n");
  }
  return 0;
}
