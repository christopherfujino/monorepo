#include <stdio.h>
#include <stdlib.h> // malloc(), size_t
#include <string.h> // strlen()

#include "box.h"
#include "chrislib.h"
#include "common.h"
#include "raylib.h"

void render_target_dispose(RenderTarget *target) {
  switch (target->type) {
  case widgetTypeBuffer:
    return;
  case widgetTypeTxt:
    // TODO: who should own this?
    free((char *)target->txt);
    return;
  }
}

Line *line_new() {
  constexpr size_t initial_buflen = 128;
  Line *lptr = malloc(sizeof(Line));
  *lptr = (Line){
      .cap = initial_buflen,
      .len = 0,
      .data = calloc(1, sizeof(char) * initial_buflen),
      .next = nullptr,
  };
  return lptr;
}

void line_append(Line *buffer, size_t n, uint8_t data[static n]) {
  // buffer->len does not include trailing NULL byte
  size_t available = buffer->cap - buffer->len;
  if (n > available) {
    debug("resizing buffer! cap = %ld, len = %ld, n = %ld\n", buffer->cap,
          buffer->len, n);
    buffer->cap *= 2;
    buffer->data = realloc(buffer->data, buffer->cap * sizeof(uint8_t));
    if (buffer->data == nullptr) {
      perror("realloc() failed");
      panic("out of memory");
    }
  }
  if (n == 1) {
    buffer->data[buffer->len] = *data;
  } else {
    // buffer->len to chomp over NULL byte
    memcpy(buffer->data + buffer->len, data, n);
  }
  buffer->len += n;
  buffer->data[buffer->len] = '\0';
}

// TODO: optimize this
// we can universally realloc() instead of memcpy() if starting_index == 0
void line_resize(Line *buffer, size_t starting_index, size_t ending_index) {
  size_t new_size = ending_index - starting_index + 1;
  if (new_size > buffer->cap) {
    if (buffer->cap < new_size) {
      buffer->data = realloc(buffer->data, new_size);
      if (buffer->data == nullptr) {
        perror("realloc() failed");
        panic("out of memory");
      }
      buffer->cap = new_size;
    }
  }
  uint8_t *new_buffer = calloc(1, buffer->cap);
  memcpy(new_buffer, buffer->data + starting_index, new_size);
  uint8_t *old_buffer = buffer->data;
  buffer->data = new_buffer;
  buffer->len = new_size;
  free(old_buffer);
}

[[nodiscard]]
void *line_dispose(Line *line) {
  free(line->data);
  free(line);
  return nullptr;
}

Line *buffer_get_previous_line(Buffer *buffer, Line *after) {
  for (Line *current = buffer->first; current != nullptr;
       current = current->next) {
    if (current->next == after) {
      return current;
    }
  }
  return nullptr;
}

Window window_init(const char *font_path) {
  Window w = calloc(1, sizeof(struct _Window));
  constexpr int screen_width = 600;
  constexpr int screen_height = 400;
  InitWindow(screen_width, screen_height, "Title");
  SetTargetFPS(60);
  // TODO
  auto font = LoadFont(font_path);

  auto first_line = line_new();
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
      .buffer =
          (Buffer){
              .first = first_line,
              .current = first_line,
          },
      .kbd_state =
          (KeyboardState){
              .left_shift = false,
          },
  };
  return w;
}

Widget widget_of_buffer(Buffer buffer) {
  return (Widget){
      .type = widgetTypeBuffer,
      .buffer = buffer,
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
        .txt = str,
    };
  }
  case widgetTypeBuffer: {
    Buffer buffer = widget->buffer;
    size_t max_width = 0;
    size_t max_height = 0;
    for (Line *lptr = buffer.first; lptr != nullptr; lptr = lptr->next) {
      size_t str_len = strlen((char *)lptr->data);
      if (str_len > max_width) {
        max_width = str_len;
      }
      max_height += 1;
    }
    return (RenderTarget){
        .size = (Size){.x = (max_width * win->font_width) + win->padding * 2,
                       .y = (max_height * win->font_height) + win->padding * 2},
        .buffer = buffer,
    };
  }
  }
}

void window_dispose(Window _) { CloseWindow(); }
void window_render(Window win, RenderTarget target, Vector2 top_left) {
  switch (target.type) {
  case widgetTypeTxt: {
    // TODO: border?
    DrawRectangle(top_left.x, top_left.y, target.size.x, target.size.y,
                  win->color2);
    DrawTextEx(win->font, target.txt,
               (Vector2){.x = top_left.x + win->padding,
                         .y = top_left.y + win->padding},
               win->font_height, 0, win->color4);
    break;
  }
  case widgetTypeBuffer: {
    DrawRectangle(top_left.x, top_left.y, target.size.x, target.size.y,
                  win->color2);
    Line *current_line = target.buffer.first;
    size_t line_count = 0;
    while (current_line != nullptr) {
      DrawTextEx(win->font, (char *)current_line->data,
                 (Vector2){.x = top_left.x + win->padding,
                           .y = top_left.y + win->padding +
                                win->font_height * line_count},
                 win->font_height, 0, win->color4);
      line_count += 1;
      current_line = current_line->next;
    }
  }
  }
  render_target_dispose(&target);
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
