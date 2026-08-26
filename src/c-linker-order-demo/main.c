#include <stdio.h>

extern int foo();

int main(void) {
  printf("%d\n", foo());
}
