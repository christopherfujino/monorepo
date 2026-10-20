# Non-turing Complete Language

```
val MAX_LEN = 128

fun main(len : Int, safe : Bool, label : String) -> String {
    if safe {
        if len > MAX_LEN {
            fail("len of ${len} is greater than MAX_LEN ${MAX_LEN}!")
        }
        "Out: " + label
    } else {
        label
    }
}
```

```
require [
    n : Int,
]
```

## Types

- Primitives
    - Booleans
    - Null
    - Numbers
    - Strings

Enumerations:

```
enum Color {
    red,
    green,
    blue,
}

let foo : Color = .red
```
