package main

import "core:fmt"

fib :: proc(n : int) -> int {
  if n <= 1 {
    return n
  }
  return fib(n - 2) + fib (n - 1)
}

main :: proc() {
  fmt.printf("The answer is: %d\n", fib(9))
}
