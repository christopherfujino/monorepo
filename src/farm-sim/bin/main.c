#include "render.h"
#include "update_state.h"

int main() {
  auto handle = gameStateInit();
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    render(handle);
    updateState(handle, dt);
  }
  gameStateDispose(handle);
  return 42;
}
