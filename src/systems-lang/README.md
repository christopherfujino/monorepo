C Problems to solve:
- Buffer overflows
    - Solution: slices, which is pointer + len, with bounds checking
- Lack of generic types, Data Types not DRY
    - Solution: parametric polymorphism (maybe on modules?)
- Lack of hygenic macros
    - Solution: ??
- Global namespace
    - Solution: name mangling (with clean opt-out)?
    - Module private identifiers
- null dereference
    - Option types, with operator overloading
- error handling
    - ?

C, plus:

Sugar:
- synctactical sugar for: `Foo *fooPtr = malloc(sizeof(Foo));`
- struct methods (`foo.get(1)` is sugar for `Bar foo_get(Foo *self, int index)`)

Features:
- modules
    - module interfaces
    - 
- unique_ptr and shared_ptr
    - `move` keyword
- tagged unions (with compiler checking)
    - maybe anonymous tagged unions?
- `defer`
- operator overloading

Keywords:
- `move`
- `val`
- `var`
