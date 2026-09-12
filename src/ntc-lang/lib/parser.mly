(* Header *)
%{
  open Ast
%}

(* Declarations *)
%token <int> INT

(* Operators *)
%token PLUS
%token MINUS
%token PRODUCT
%token DIVIDE

%token EOF

%start <expr> prog

(* These rows are ordered from low to high precedence *)
%left PLUS MINUS
%left PRODUCT DIVIDE

%%

(* Rules *)

prog:
  | e = expr; EOF { e }
  | EOF { Unit }

expr:
  | e1 = expr; PLUS; e2 = expr { Binary (Plus, e1, e2) }
  | e1 = expr; MINUS; e2 = expr { Binary (Minus, e1, e2) }
  | e1 = expr; PRODUCT; e2 = expr { Binary (Product, e1, e2) }
  | e1 = expr; DIVIDE; e2 = expr { Binary (Divide, e1, e2) }
  | i = INT { Int i }
