type operator =
  | Plus
  | Minus
  | Product
  | Divide

and expr =
  (* TODO *)
  | Int of int
  | Binary of operator * expr * expr
  | Unit

let op_to_s = function
  | Plus -> "+"
  | Minus -> "-"
  | Product -> "*"
  | Divide -> "/"

let rec to_s = function
  | Int i -> Printf.sprintf "Int(%d)" i
  | Binary (op, e1, e2) ->
      Printf.sprintf "Binary(%s %s %s)" (to_s e1) (op_to_s op) (to_s e2)
  | Unit -> "unit"
