type expr =
  (* TODO *)
  | Int of int
  | Null

let to_s = function
  | Int i -> Printf.sprintf "Int(%d)" i
  | Null -> "null"
