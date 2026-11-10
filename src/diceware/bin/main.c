#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  size_t len;
  char *str;
} Word;

const char *words[] = {
    "foo",
    "bar",
    "baz",
    "qux",
};

Word wordNew(char *str) {
  size_t len = strlen(str);
  return (Word){
      .len = len,
      .str = str,
  };
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
  stpcpy(output.str, a.str);
  abort();
  a = wordDispose(a);
  b = wordDispose(b);
}

Word getWord() {
  // TODO
  abort();
}

int main(void) {
  // TODO: parameterize
  constexpr unsigned char n = 4;
  for (unsigned char i = 0; i < n; i++) {
  }
  return 0;
}
