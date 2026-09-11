(* Header *)
{
  open Parser
}

let white = [' ' '\t']+
let digit = ['0'-'9']
let lone_digit = ['1'-'9']
let int = '-'? lone_digit digit*

rule read = parse
  | white { (read [@tailcall]) lexbuf }
  | '+' { PLUS }
  | int { INT (int_of_string (Lexing.lexeme lexbuf)) }
  (* eof is ocamllex built-in *)
  | eof { EOF }
  | _ {failwith @@ Printf.sprintf "dunno how to lex \"%s\"" @@ Lexing.lexeme lexbuf}

(* Footer *)
{
}
