(* Header *)
{
  open Parser
}

let white = [' ' '\t']+

rule read = parse
  | _ { EOF }
