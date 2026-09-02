#ifndef __src_kaleidoscope_include_lexer_h
#define __src_kaleidoscope_include_lexer_h

// All other tokens with be their ASCII value.
enum Token {
  // This should never happen
  tok_unreachable = 0,

  tok_eof = -1,

  // commands
  tok_def = -2,
  tok_extern = -3,

  // primary
  tok_identifier = -4,
  tok_number = -5,
};

int gettok();

extern char *IdentifierStr;
extern double NumVal;

#endif // __src_kaleidoscope_include_lexer_h
