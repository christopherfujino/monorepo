let () =
  let lexbuf = Lexing.from_string "42" in
  let _ = Ntc_lang.Parser.prog Ntc_lang.Lexer.read lexbuf in
  print_endline "Non-turing complete language!"
