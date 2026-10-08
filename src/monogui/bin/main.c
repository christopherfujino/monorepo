#include "raylib.h"
#include "render.h"

int main(void) {
  RenderState state = render_state_new();
  while (!WindowShouldClose()) {
    render(state, widget_text_new("Yolo dawg"));
  }
  render_state_dispose(state);

  return 0;
}
