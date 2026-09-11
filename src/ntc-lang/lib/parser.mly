(* Header *)
%{
  open Ast
%}

(* Declarations *)
%token <int> INT
%token EOF

%start <expr> prog

%%

(* Rules *)

prog:
  | i = INT { Int i }
  | EOF { Null }
