#include "parser.h"

#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

static llvm::LLVMContext *TheContext = new llvm::LLVMContext();

llvm::Value *codegenExpr(Expr *expr) {
  switch (expr->type) {
    case Expr::expr_type_bin:
      abort();
    case Expr::expr_type_call:
      abort();
    case Expr::expr_type_num:
      abort();
    case Expr::expr_type_ref:
      abort();
  }
  return nullptr;
}
