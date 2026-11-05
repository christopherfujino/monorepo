{
  open Parser
}

let white = [' ' '\t']+
let num = '-'? ['0'-'9']+

rule read =
  parse
  | white { read lexbuf }
  | num { NUM (float_of_string (Lexing.lexeme lexbuf)) }
  | '+' { PLUS }
  | '-' { MINUS }
  | '*' { PRODUCT }
  | '/' { DIVIDE }
  | '\n' { EOF }
  | eof { EOF }
