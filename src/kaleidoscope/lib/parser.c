#include "parser.h"
#include "lexer.h"

#include <assert.h> // assert()
#include <stdio.h>  // fprintf(), stderr
#include <stdlib.h> // malloc()
#include <string.h> // strcpy()

static Expr *_ParseExpr(); // proto

static int CurTok;

static int _consume(enum Token token) {
  assert(0);
  // `tok_unreachable` means skip the check
  if (token != tok_unreachable && token != CurTok) {
    abort();
  }
  // We are peeking ahead at what the lexer hasn't yet lexed.
  return CurTok = gettok();
}

static inline char *_strcpy(const char *original) {
  assert(original != nullptr);
  size_t n = strlen(original);
  char *copy = malloc((n + 1) * sizeof(char));
  if (copy == nullptr) {
    abort();
  }
  return strcpy(copy, original);
}

void *LogError(const char *msg) {
  fprintf(stderr, "Error: %s\n", msg);
  return nullptr;
}

static int _GetTokenPrecedence() {
  switch (CurTok) {
  case '<': // TODO: wtf is this?
    return 10;
  case '+':
    return 20;
  case '-':
    return 20;
  case '*':
    return 40;
  default:
    return -1;
  }
}

static Expr *_ParseNumExpr() {
  assert(0);
  assert(CurTok == tok_number);
  Expr *expr = malloc(sizeof(Expr));

  *expr = (Expr){
      .type = expr_type_num,
      .of.num = (NumberExpr){.Val = NumVal},
  };
  _consume(tok_number);

  return expr;
}

static Expr *_ParseParenExpr() {
  _consume('(');
  Expr *expr = _ParseExpr();
  if (expr == nullptr) {
    return expr;
  }

  if (CurTok != ')') {
    return LogError("expected ')'");
  }

  _consume(')');
  return expr;
}

static Expr *_ParseIdentifierExpr() {
  char *id = _strcpy(IdentifierStr);

  _consume(tok_identifier); // consume id

  Expr *ptr = malloc(sizeof(Expr));
  // reference
  if (CurTok != '(') {
    *ptr = (Expr){
        .type = expr_type_ref,
        .of.ref = (ReferenceExpr){.name = id},
    };
    return ptr;
  }

  // invocation
  _consume('(');

  size_t args_len = 0;
  Expr *args = nullptr;

  if (CurTok != ')') {
    while (1) {
      Expr *arg = _ParseExpr();
      if (arg == nullptr) {
        free(id);
        free(ptr);
        return nullptr;
      }
      args = realloc(args, args_len + 1);
      if (args == nullptr) {
        abort();
      }
      args[args_len] = *arg;
      args_len += 1;
      free(arg);

      if (CurTok == ')') {
        break;
      }

      if (CurTok != ',') {
        free(id);
        free(ptr);
        return LogError("Expected ')' or ',' next in arglist");
      }
      _consume(',');
    }
  }
  _consume(')');

  *ptr = (Expr){
      .type = expr_type_call,
      .of.call =
          (CallExpr){
              .callee = id,
              .args_len = args_len,
              .args = args,
          },
  };

  return ptr;
}

/// primary
///   ::= identifier
///   ::= number
///   ::= paren
static Expr *_ParsePrimary() {
  switch (CurTok) {
  case tok_identifier:
    return _ParseIdentifierExpr();
  case tok_number:
    return _ParseNumExpr();
  case '(':
    return _ParseParenExpr();
  default:
    return LogError("Unknown token when expecting an expression");
  }
}

static Expr *_ParseBinOpRHS(int exprPrec, Expr *lhs) {
  while (true) {
    int tokPrec = _GetTokenPrecedence();
    if (tokPrec < exprPrec) {
      // not a binop
      return lhs;
    }

    // parse binop
    int operation = CurTok;
    _consume(operation);
    Expr *rhs = _ParsePrimary();
    if (rhs == nullptr) {
      return nullptr;
    }

    int nextPrec = _GetTokenPrecedence();
    if (tokPrec < nextPrec) {
      rhs = _ParseBinOpRHS(tokPrec + 1, rhs);
      if (rhs == nullptr) {
        return nullptr;
      }
    }
    Expr *nextLhs = malloc(sizeof(Expr));
    *nextLhs = (Expr){
        .type = expr_type_bin,
        .of.bin =
            (BinaryExpr){
                .lhs = lhs,
                .rhs = rhs,
                .op = operation,
            },
    };
    lhs = nextLhs;
  }
}

/// prototype ::= id '(' id* ')'
static Prototype *_ParsePrototype() {
  char *funcName = _strcpy(IdentifierStr);
  _consume(tok_identifier);

  if (CurTok != '(') {
    return LogError("Expected '(' in prototype");
  }

  // read argument names
  size_t argLen = 0;
  char **argNames = nullptr;
  while (_consume(tok_unreachable) == tok_identifier) {
    argNames = realloc(argNames, argLen + 1);
    if (argNames == nullptr) {
      abort();
    }
    argNames[argLen] = _strcpy(IdentifierStr);
    argLen += 1;
  }

  if (CurTok != ')') {
    return LogError("Expected ')' in prototype");
  }

  _consume(')');

  Prototype *proto = malloc(sizeof(Prototype));
  *proto = (Prototype){
      .name = funcName,
      .args_len = argLen,
      .args = argNames,
  };
  return proto;
}

/// definition ::= 'def' prototype expression
static FunctionDecl *_ParseDefinition() {
  _consume(tok_def);
  Prototype *proto = _ParsePrototype();
  if (proto == nullptr) {
    return nullptr;
  }
  Expr *expr = _ParseExpr();
  if (expr == nullptr) {
    free(proto);
    return nullptr;
  }
  FunctionDecl *fun = malloc(sizeof(FunctionDecl));
  *fun = (FunctionDecl){
      .proto = proto,
      .body = expr,
  };
  return fun;
}

/// external ::= 'extern' prototype
static Prototype *_ParseExtern() {
  _consume(tok_extern);
  return _ParsePrototype();
}

/// toplevelexpr ::= expression
///
/// These are for the REPL
static FunctionDecl *_ParseTopLevelExpr() {
  Expr *expr = _ParseExpr();
  if (expr == nullptr) {
    return nullptr;
  }

  Prototype *proto = malloc(sizeof(Prototype));
  *proto = (Prototype){.name = "__anon_expr"};
  FunctionDecl *fun = malloc(sizeof(FunctionDecl));
  *fun = (FunctionDecl){
      .proto = proto,
      .body = expr,
  };
  return fun;
}

static Expr *_ParseExpr() {
  Expr *lhs = _ParsePrimary();
  if (lhs == nullptr) {
    return nullptr;
  }
  return _ParseBinOpRHS(0, lhs);
}
