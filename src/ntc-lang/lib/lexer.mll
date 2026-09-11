(* Header *)
{
  open Parser
}

let white = [' ' '\t']+
let digit = ['0'-'9']
let lone_digit = ['1'-'9']
let int = '-'? lone_digit digit*

rule read = parse
  | int { INT (int_of_string (Lexing.lexeme lexbuf)) }
