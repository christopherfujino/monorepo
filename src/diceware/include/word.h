#ifndef MONOREPO_SRC_DICEWARE_INCLUDE_WORD_H
#define MONOREPO_SRC_DICEWARE_INCLUDE_WORD_H

#include <stddef.h>

typedef struct {
  size_t len;
  char *str;
} Word;

Word wordNew(const char *str);

[[nodiscard]]
Word wordDispose(Word word);

/// Will dispose its arguments.
[[nodiscard]]
Word wordCat(Word a, Word b);

Word getWord();

#endif // MONOREPO_SRC_DICEWARE_INCLUDE_WORD_H
