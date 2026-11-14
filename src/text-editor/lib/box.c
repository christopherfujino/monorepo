#include <stdio.h>
#include <stdlib.h> // malloc(), size_t
#include <string.h> // strlen()

#include "box.h"
#include "chrislib.h"
#include "common.h"
#include "raylib.h"

void buffer_add(Buffer *buffer, size_t n, uint8_t data[static n]) {
  // buffer->len does not include trailing NULL byte
  size_t available = buffer->cap - buffer->len;
  if (n > available) {
    debug("resizing buffer! cap = %ld, len = %ld, n = %ld\n", buffer->cap, buffer->len, n);
    buffer->cap *= 2;
    buffer->data = realloc(buffer->data, buffer->cap * sizeof(uint8_t));
    if (buffer->data == nullptr) {
      perror("realloc() failed");
      panic("out of memory");
    }
  }
  // buffer->len - 1 to chomp over NULL byte
  memcpy(buffer->data + buffer->len - 1, data, n);
  buffer->len += n;
  buffer->data[buffer->len - 1] = '\0';
}

Window window_init(const char *font_path) {
  Window w = calloc(1, sizeof(struct _Window));
  constexpr int screen_width = 600;
  constexpr int screen_height = 400;
  InitWindow(screen_width, screen_height, "Title");
  SetTargetFPS(60);
  // TODO
  auto font = LoadFont(font_path);

  // 2K
  constexpr size_t initial_buflen = 1 << 11;
  auto buffer = (Buffer){.cap = initial_buflen,
                         .len = 0,
                         .data = calloc(1, sizeof(char) * initial_buflen)};
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
      .buffer = buffer,
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

void window_render_loop(Window win, WindowRenderCallback r,
                        UpdateStateCallback u) {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(win->color0);

    u(win);
    r(win);

    EndDrawing();
  }
}
