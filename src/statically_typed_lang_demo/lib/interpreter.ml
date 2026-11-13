type t =
  | Num of float

let to_s = function
  | Num f -> Float.to_string f

let interpret (node : Ast.expr) : t = match node.expr with
  | Num f -> Num f
  | Binary (e1, op, e2) -> failwith "TODO"
