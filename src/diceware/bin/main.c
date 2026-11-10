#include <stdio.h>  // printf()
#include <stdlib.h> // rand(), srand()
#include <time.h>   // time()

#if defined(__linux__)
#include <sys/random.h> // getrandom()
#else
#error "TODO: figure out non-linux random number seeding"
#endif

#include "clipboard.h"
#include "word.h"

void seed() {
  unsigned int seed = 0;
  ssize_t result = getrandom(&seed, sizeof(seed), 0x0);
  if (result < 0) {
    perror("getrandom() failed");
    abort();
  } else if ((size_t)result < sizeof(seed)) {
    fprintf(stderr, "Expected %ld bytes but got %ld\n", result, sizeof(seed));
    abort();
  }

  srand(seed);
}

int main(void) {
  // TODO: parameterize
  constexpr unsigned char n = 4;
  seed();

  Word w = wordNew("");
  for (unsigned char i = 0; i < n; i++) {
    w = wordCat(w, getWord());
  }
  // TODO: consider using `zenity` if no TTY attached
  bool clipboarded = clipboard(w.str);
  printf("\n%s\n\n", w.str);
  if (clipboarded) {
    printf("  \U0001F4CB Copied to X11 clipboard!\n");
  }
  return 0;
}
