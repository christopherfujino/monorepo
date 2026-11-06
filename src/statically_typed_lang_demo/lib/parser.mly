%{

%}

%token PLUS
%token MINUS
%token PRODUCT
%token DIVIDE
%token EOF
%token <float> NUM

%start <float> stmt

%%

stmt:
  | e = expr1; EOF { e }

expr1:
  | e1 = expr1; PLUS; e2 = expr2 { e1 +. e2 }
  | e1 = expr1; MINUS; e2 = expr2 { e1 -. e2 }
  | e = expr2 { e }

expr2:
  | e1 = expr2; PRODUCT; e2 = expr3 { e1 *. e2 }
  | e1 = expr2; DIVIDE; e2 = expr3 { e1 /. e2 }
  | e = expr3 { e }

expr3:
  | n = NUM { n }
