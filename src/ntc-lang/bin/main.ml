let rec main () =
  Printf.printf "> %!";
  let open Ntc_lang in
  match In_channel.input_line In_channel.stdin with
  | None -> print_endline "EOF"
  | Some line ->
      let lexbuf = Lexing.from_string line in
      let prog = Parser.prog Lexer.read lexbuf in
      List.iter (fun e -> print_endline @@ Ast.to_s e) prog.exprs;
      (main [@tailcall]) ()

let () =
  try main () with
  | Failure msg ->
      Printf.printf "%s\n" msg;
      exit 1
  | _ as e ->
      print_endline "TODO explicitly handle this exception in bin/main.ml";
      Printexc.to_string e |> print_endline;
      exit 1
