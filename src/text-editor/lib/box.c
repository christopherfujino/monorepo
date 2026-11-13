#include <stdlib.h> // malloc(), size_t
#include <string.h> // strlen()

#include "box.h"
#include "common.h" // TODO: remove this dep
#include "raylib.h"

Window window_init() {
  Window w = malloc(sizeof(struct _Window));
  constexpr int screen_width = 600;
  constexpr int screen_height = 400;
  InitWindow(screen_width, screen_height, "Title");
  SetTargetFPS(60);
  // TODO
  auto font = LoadFont("../../3p/fonts/mononoki/mononoki-spritesheet.fnt");

  *w = (struct _Window){
      .color0 = GetColor(0x000000FF),
      .color2 = GetColor(0x888888FF),
      .color4 = GetColor(0xFFFFFFFF),
      .font = font,
      .font_height = 32,
      .font_width = 16,
      .screen_height = screen_height,
      .screen_width = screen_width,
      .padding = 1,
  };
  return w;
}
Widget widget_of_txt(const char *string) {
  size_t len = strlen(string) + 1;
  char *ptr = malloc(len * sizeof(char));
  strncpy(ptr, string, len);
  return (Widget){
      .type = widgetTypeTxt,
      .txt = ptr,
  };
}

RenderTarget widget_layout(Window win, Widget *widget,
                           [[maybe_unused]] Constraints constraints) {
  switch (widget->type) {
  case widgetTypeTxt: {
    const char *str = widget->txt;
    size_t str_len = strlen(str);
    // TODO: check strlen and break lines
    return (RenderTarget){
        .size = (Size){.x = (str_len * win->font_width) + win->padding * 2,
                       .y = (1 * win->font_height) + win->padding * 2},
        .txt = {.str = str}};
  } break;
  }
}

void window_dispose(Window _) { CloseWindow(); }
void window_render(Window win, RenderTarget target, Vector2 top_left) {
  switch (target.type) {
  case widgetTypeTxt: {
    // TODO: border?
    debug("size = (%f, %f)\n", target.size.x, target.size.y);
    DrawRectangle(top_left.x, top_left.y, target.size.x, target.size.y,
                  win->color2);
    const char *str = target.txt.str;
    DrawTextEx(win->font, str,
               (Vector2){.x = top_left.x + win->padding,
                         .y = top_left.y + win->padding},
               win->font_height, 0, win->color4);
  } break;
  }
}

void window_render_loop(Window win, WindowRenderCallback r) {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(win->color0);

    r(win);

    EndDrawing();
  }
}
