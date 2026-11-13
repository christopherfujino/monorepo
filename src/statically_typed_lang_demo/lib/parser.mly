%{
open Ast
%}

%token <Lexing.position> PLUS
%token <Lexing.position> MINUS
%token <Lexing.position> PRODUCT
%token <Lexing.position> DIVIDE
%token EOF
%token <float * Lexing.position> NUM

%start <expr> stmt

%%

stmt:
  | e = expr1; EOF { e }

expr1:
  | e1 = expr1; PLUS; e2 = expr2 {
    { expr = Binary(e1, Plus, e2);
      pos = e1.pos; }
  }
  | e1 = expr1; MINUS; e2 = expr2 {
    { expr = Binary(e1, Minus, e2);
      pos = e1.pos; }
  }
  | e = expr2 { e }

expr2:
  | e1 = expr2; PRODUCT; e2 = expr3 {
    {
      expr = Binary (e1, Product, e2);
      pos = e1.pos;
    }
  }
  | e1 = expr2; DIVIDE; e2 = expr3 {
    {
      expr = Binary (e1, Divide, e2);
      pos = e1.pos;
    }
  }
  | e = expr3 { e }

expr3:
  | n = NUM {
    let (num, pos) = n in
    {
      expr = Num num;
      pos = pos;
    }
  }
