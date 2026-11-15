#ifndef MONOREPO_SRC_TXT_INCLUDE_COMMON_H
#define MONOREPO_SRC_TXT_INCLUDE_COMMON_H

#include <stdarg.h>
#include <stdio.h>

[[gnu::format(printf, 1, 2)]]
static inline void print(const char *restrict fmt, ...) {
#ifdef NDEBUG
// no-op
#else
  va_list args;
  va_start(args);
  vfprintf(stderr, fmt, args);
  va_end(args);
#endif
}

/// For debug-level tracing.
[[gnu::format(printf, 1, 2)]]
static inline void debug([[maybe_unused]]const char *restrict fmt, ...) {
#ifdef DEBUG_TRACING
  va_list args;
  va_start(args);
  vfprintf(stderr, fmt, args);
  va_end(args);
#else
// no-op
#endif
}

#endif // MONOREPO_SRC_TXT_INCLUDE_COMMON_H
