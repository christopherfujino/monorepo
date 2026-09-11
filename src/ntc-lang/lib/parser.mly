(* Header *)
%{
  open Ast
%}

(* Declarations *)
%token EOF

%start <unit> prog

%%

(* Rules *)

prog:
  | EOF { () }
