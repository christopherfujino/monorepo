#ifndef __SRC_KALEIDOSCOPE_INCLUDE_PARSER_H
#define __SRC_KALEIDOSCOPE_INCLUDE_PARSER_H

#include <stddef.h> // size_t

// Forward declaration
struct Expr;

typedef struct NumberExpr {
  double Val;
} NumberExpr;

typedef struct ReferenceExpr {
  char *name;
} ReferenceExpr;

typedef struct BinaryExpr {
  struct Expr *lhs, *rhs;
  char op;
} BinaryExpr;

typedef struct CallExpr {
  char *callee;
  size_t args_len;
  struct Expr *args;
} CallExpr;

typedef struct Expr {
  enum {
    expr_type_num,
    expr_type_ref,
    expr_type_bin,
    expr_type_call,
  } type;
  union {
    NumberExpr num;
    ReferenceExpr ref;
    BinaryExpr bin;
    CallExpr call;
  } of;
} Expr;

typedef struct Prototype {
  char *name;
  size_t args_len;
  char **args;
} Prototype;

typedef struct FunctionDecl {
  Prototype *proto;
  Expr *body;
} FunctionDecl;

#endif // __SRC_KALEIDOSCOPE_INCLUDE_PARSER_H
