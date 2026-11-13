type expr = {
  expr : expr_t;
  pos : Lexing.position
}

and operator =
  | Plus
  | Minus
  | Product
  | Divide

and expr_t =
  | Num of float
  | Binary of expr * operator * expr
