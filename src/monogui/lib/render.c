#include <stdlib.h> // malloc()

#include "raylib.h"
#include "render.h"
#include "widget.h"

struct _RenderState {
  void *nil;
};

static constexpr int initialWidth = 1000;
static constexpr int initialHeight = 750;
static constexpr int fps = 60;

RenderState render_state_new() {
  InitWindow(initialWidth, initialHeight, "monogui");
  SetTargetFPS(fps);
  RenderState ptr = malloc(sizeof(struct _RenderState));
  *ptr = (struct _RenderState){.nil = nullptr};
  return ptr;
}

static void _render_widget(RenderState, Widget w) {
  switch (w.tag) {
  case widget_text:
    // TODO: DrawTextEx()
    constexpr int x = 40;
    constexpr int y = 40;
    constexpr int fontSize = 12;
    constexpr Color color = (Color){0xFF, 0xFF, 0xFF, 0xFF};
    DrawText(w.text, x, y, fontSize, color);
    break;
  }
}

void render_state_dispose(RenderState state) {
  CloseWindow();
  free(state);
}

void render(RenderState rs, Widget tree) {
  BeginDrawing();
  {
    ClearBackground(color0);
    _render_widget(rs, tree);
    DrawFPS(10, 10);
  }
  EndDrawing();
}
