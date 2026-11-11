#ifndef __MONOREPO_SRC_CHRISLIB_CHRISLIB_H
#define __MONOREPO_SRC_CHRISLIB_CHRISLIB_H

#include <stdarg.h> // va_list, va_start()

typedef struct {
  enum {
    resultTagOk,
    resultTagErr,
  } tag;
  union {
    const void *ok;
    const char *err;
  };
} Result;

void resultDispose(Result *result);

[[nodiscard]]
Result resultOk();

[[gnu::format(printf, 1, 2)]] [[nodiscard]]
Result resultErr(const char *fmt, ...);

void resultTry(Result result);
// basically `man 3 asprintf`
[[gnu::format(printf, 2, 3)]] [[nodiscard]]
Result chrisprintf(char **strp, const char *fmt, ...);

[[nodiscard]]
Result vchrisprintf(char **strp, const char *fmt, va_list args);

[[noreturn, gnu::format(printf, 1, 2)]]
void panic(const char *fmt, ...);

#ifdef CHRISLIB_IMPL
#include <stdio.h>  // stderr, vfprintf()
#include <stdlib.h> // abort()
#include <string.h> // strncpy()

// Ensure it is ok
void resultTry(Result result) {
  switch (result.tag) {
  case resultTagOk:
    return;
  case resultTagErr:
    panic("%s", result.err);
    break;
  }
}

void resultDispose(Result *result) {
  switch (result->tag) {
  case resultTagOk:
    return;
  case resultTagErr:
    free((void *)result->err);
  }
}

Result resultOk() {
  return (Result){
      .tag = resultTagOk,
      .ok = nullptr,
  };
}

void panic(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  fflush(stderr);
  va_end(args);
#ifdef NDEBUG
  exit(1);
#else
  abort();
#endif
}

Result vchrisprintf(char **strp, const char *fmt, va_list args) {
  constexpr size_t initialBuflen = 512;
  size_t currentBuflen = initialBuflen;
  static char staticBuf[initialBuflen];
  char *buf = staticBuf;
  int n = 0;

  while (1) {
    n = vsnprintf(buf, currentBuflen, fmt, args);
    // TODO validate n
    if (n < 0) {
      return resultErr("vsnprintf() failed");
    } else if (n == (int)currentBuflen) {
      currentBuflen *= 2;
      if (buf == staticBuf) {
        buf = malloc(currentBuflen);
      } else {
        buf = realloc(buf, currentBuflen);
      }
      if (buf == nullptr) {
        return resultErr("failed to allocate memory");
      }
    } else {
      // success
      break;
    }
  }

  *strp = malloc(n + 1);
  strncpy(*strp, buf, n);
  (*strp)[n] = '\0';
  if (buf != staticBuf) {
    free(buf);
  }
  return resultOk();
}

Result chrisprintf(char **restrict strp, const char *restrict fmt, ...) {
  va_list args = {};
  va_start(args);
  Result result = vchrisprintf(strp, fmt, args);
  va_end(args);

  return result;
}

Result resultErr(const char *fmt, ...) {
  char *msg = nullptr;
  va_list args = {};
  {
    va_start(args, fmt);
    resultTry(vchrisprintf(&msg, fmt, args));
    va_end(args);
  }

  return (Result){
      .tag = resultTagErr,
      .err = msg,
  };
}
#endif // CHRISLIB_IMPL

#endif // __MONOREPO_SRC_CHRISLIB_CHRISLIB_H
