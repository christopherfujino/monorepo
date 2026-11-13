open Statically_typed_lang_demo

let rec repl () =
  Printf.printf "> %!";
  let buf = Lexing.from_channel In_channel.stdin in
  let ast = Parser.stmt Lexer.read buf in
  let value = Interpreter.interpret ast in
  print_endline @@ Interpreter.to_s value;
  repl ()

let () = repl ()
