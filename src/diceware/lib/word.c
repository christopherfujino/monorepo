#include <stdlib.h> // malloc()
#include <string.h> // strlen()

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

Word getWord() {
  // TODO: use mtrand
  int n = rand() % (sizeof(dictionary) / sizeof(char *));
  Word word = wordNew(dictionary[n]);
  // toUpper
  word.str[0] -= 32;
  return word;
}


