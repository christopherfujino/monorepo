type t =
  (* any? do we support subtyping and downcasts? *)
  | Bool
  | Int
  | String
  | Unit
  | List of t
  | Map of t * t
  | Union of t list
  | User of { fields : (string * t) list }
