#include <stddef.h> // uint8_t
#include <stdint.h> // size_t
#include <stdio.h>  // printf()
#include <stdlib.h> // abort()

typedef enum Enum : uint8_t {
  Foo,
  Bar,
  Baz,

  EnumCount,
} Enum;

int main(void) {
  Enum vals[EnumCount] = {Foo, Bar, Baz};

  for (size_t i = 0; i < EnumCount; i++) {
    switch (vals[i]) {
      case Foo:
        printf("Foo = %d\n", vals[i]);
        break;
      case Bar:
        printf("Bar = %d\n", vals[i]);
        break;
      case Baz:
        printf("Baz = %d\n", vals[i]);
        break;
      default:
        abort();
    }
  }
}
