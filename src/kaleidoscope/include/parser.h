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

typedef struct PrototypeDecl {
  char *name;
  size_t args_len;
  char **args;
} PrototypeDecl;

typedef struct FunctionDecl {
  PrototypeDecl *proto;
  Expr *body;
} FunctionDecl;

typedef struct Decl {
  enum {
    decl_type_proto,
    decl_type_func,
  } type;
  union {
    PrototypeDecl proto;
    FunctionDecl func;
  } of;
} Decl;

#endif // __SRC_KALEIDOSCOPE_INCLUDE_PARSER_H
