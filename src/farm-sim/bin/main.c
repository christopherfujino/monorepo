#include "render.h"

int main() {
  auto handle = gameStateInit();
  render(handle);
  gameStateDispose(handle);
  return 42;
}
