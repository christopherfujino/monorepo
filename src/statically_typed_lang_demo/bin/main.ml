open Statically_typed_lang_demo

let rec repl () =
  Printf.printf "> %!";
  let buf = Lexing.from_channel In_channel.stdin in
  let f = Parser.stmt Lexer.read buf in
  Printf.printf "%f\n" f;
  repl ()

let () = repl ()
