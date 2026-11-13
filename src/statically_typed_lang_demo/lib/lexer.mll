{
  open Parser
}

let white = [' ' '\t']+
let num = '-'? ['0'-'9']+

rule read =
  parse
  | white { read lexbuf }
  | num { NUM (float_of_string (Lexing.lexeme lexbuf), lexbuf.lex_start_p) }
  | '+' { PLUS lexbuf.lex_start_p}
  | '-' { MINUS lexbuf.lex_start_p}
  | '*' { PRODUCT lexbuf.lex_start_p}
  | '/' { DIVIDE lexbuf.lex_start_p}
  | '\n' { EOF }
  | eof { EOF }
