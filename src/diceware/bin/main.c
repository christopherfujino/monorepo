#include <stdio.h>  // printf()
#include <stdlib.h> // rand(), srand()
#include <string.h> // strlen()
#include <time.h>

#include "dictionary.h"

typedef struct {
  size_t len;
  char *str;
} Word;

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

/// Will dispose its arguments
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

Word getWord() {
  // TODO: use mtrand
  int n = rand() % (sizeof(dictionary) / sizeof(char *));
  return wordNew(dictionary[n]);
}

int main(void) {
  // TODO: parameterize
  constexpr unsigned char n = 4;
  Word w = wordNew("");
  srand(time(nullptr));
  for (unsigned char i = 0; i < n; i++) {
    w = wordCat(w, getWord());
  }
  printf("You word is: %s\n", w.str);
  return 0;
}
