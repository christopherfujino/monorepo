(* Header *)
%{
  open Ast
%}

(* Declarations *)
%token <int> INT
%token PLUS
%token EOF

%start <expr> prog

%%

(* Rules *)

prog:
  | e = expr EOF { e }
  | EOF { Null }

expr:
  | e1 = expr; op = PLUS; e2 = expr { Binary (Plus, e1, e2) }
  | i = INT { Int i }
