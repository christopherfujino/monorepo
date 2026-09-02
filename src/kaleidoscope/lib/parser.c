#include "parser.h"
#include "lexer.h"

#include <assert.h> // assert()
#include <stdio.h>  // fprintf(), stderr
#include <stdlib.h> // malloc()
#include <string.h> // strcpy()

static Expr *_ParseExpr(); // proto

static int CurTok;

static int _consume(enum Token token) {
  assert(token == CurTok);
  // We are peeking ahead at what the lexer hasn't yet lexed.
  return CurTok = gettok();
}

Expr *LogError(const char *msg) {
  fprintf(stderr, "Error: %s\n", msg);
  return nullptr;
}

PrototypeDecl *LogErrorP(const char *msg) {
  LogError(msg);
  return nullptr;
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

// TODO: _ParseParenExpr()

static Expr *_ParseIdentifierExpr() {
  size_t n = strlen(IdentifierStr);
  char *id = malloc((n + 1) * sizeof(char));
  if (id == nullptr) {
    abort();
  }
  strcpy(id, IdentifierStr);

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
