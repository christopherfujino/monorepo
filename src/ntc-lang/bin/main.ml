let rec main () =
  match In_channel.input_line In_channel.stdin with
  | None -> print_endline "EOF"
  | Some line ->
      let lexbuf = Lexing.from_string line in
      let e = Ntc_lang.Parser.prog Ntc_lang.Lexer.read lexbuf in
      print_endline @@ Ntc_lang.Ast.to_s e;
      (main [@tailcall]) ()

let () = main ()
