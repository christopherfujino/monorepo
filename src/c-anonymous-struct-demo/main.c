#include <stdio.h>

struct Foo {
  struct {
    int i;
    char c;
  };
};

int main() {
  struct Foo foo = {
    .i = 42,
    .c = 'c',
  };

  printf("(%d, %c)\n", foo.i, foo.c);
}
