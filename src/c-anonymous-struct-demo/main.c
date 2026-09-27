#include <stdio.h>

struct Foo {
  struct {
    int i;
    char c;
  } inner;
};

int main() {
  struct Foo foo = {
    .inner = {42, 'c'},
  };

  auto i = foo.inner;
  printf("(%d, %c)\n", i.i, i.c);
}
