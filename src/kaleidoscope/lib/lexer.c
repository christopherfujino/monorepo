#include "lexer.h"
#include "buffer.h"
#include <ctype.h>  // isalpha(), isalnum()
#include <stdio.h>  // getchar()
#include <stdlib.h> // strtod()
#include <string.h> // stringcmp()

char *IdentifierStr;
double NumVal;

int gettok() {
  static int LastChar = ' '; // TODO: inject

  while (isspace(LastChar)) {
    LastChar = getchar();
  }

  if (isalpha(LastChar)) { // [a-zA-Z]
    Buffer buffer = buffer_new();

    buffer_push(&buffer, (char)LastChar);
    while (isalnum((LastChar = getchar()))) { // [a-zA-Z0-9]
      buffer_push(&buffer, (char)LastChar);
    }
    char *identifier = buffer_to_string(&buffer);
    if (strcmp(identifier, "def") == 0) {
      free(identifier);
      return tok_def;
    }
    if (strcmp(identifier, "extern") == 0) {
      free(identifier);
      return tok_extern;
    }
    // It is safe to call `free(nullptr)`.
    free(IdentifierStr);
    IdentifierStr = identifier;
    return tok_identifier;
  }

  // TODO: does this handle 1.2.3?
  if (isdigit(LastChar) || LastChar == '.') {
    Buffer buffer = buffer_new();

    do {
      buffer_push(&buffer, LastChar);
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

    char *string = buffer_to_string(&buffer);

    // TODO error handling?!
    NumVal = strtod(string, nullptr);
    free(string);
    return tok_number;
  }

  if (LastChar == '#') { // comment
    do {
      LastChar = getchar();
    } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
    if (LastChar != EOF) {
      // TODO: unwind recursion
      return gettok();
    }
  }

  if (LastChar == EOF) {
    // Don't eat the EOF(?)
    return tok_eof;
  }

  // return raw ASCII value(?!)
  int cur = LastChar;
  LastChar = getchar();
  return cur;
}
