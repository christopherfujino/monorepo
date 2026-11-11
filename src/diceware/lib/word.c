#include <stdio.h>  // fprintf(), stderr
#include <stdlib.h> // malloc()
#include <stdlib.h> // rand(), srand()
#include <string.h> // strlen()
#include <time.h>   // time()
#if defined(__linux__)
#include <sys/random.h> // getrandom()
#else
#error "TODO: figure out non-linux random number seeding"
#endif

#include "dictionary.h"
#include "word.h"

Word wordNew(const char *str) {
  size_t len = strlen(str);
  Word word = (Word){
      .len = len,
      .str = malloc(len + 1),
  };
  strcpy(word.str, str);
  word.str[len] = '\0';
  return word;
}

[[nodiscard]]
Word wordDispose(Word word) {
  free(word.str);
  return (Word){
      .len = 0,
      .str = nullptr,
  };
}

[[nodiscard]]
Word wordCat(Word a, Word b) {
  size_t outputLen = a.len + b.len;
  Word output = {
      .len = outputLen,
      .str = malloc(outputLen + 1),
  };
  char *next = stpcpy(output.str, a.str);
  strcpy(next, b.str);
  a = wordDispose(a);
  b = wordDispose(b);

  return output;
}

static void seed() {
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

static bool didSeed = false;

Word getWord() {
  if (!didSeed) {
    seed();
    didSeed = true;
  }
  // TODO: use mtrand
  int n = rand() % (sizeof(dictionary) / sizeof(char *));
  Word word = wordNew(dictionary[n]);
  // toUpper
  word.str[0] -= 32;
  return word;
}
