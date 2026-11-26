#ifndef MONOREPO_SRC_TXT_INCLUDE_BOX_H
#define MONOREPO_SRC_TXT_INCLUDE_BOX_H

#include <stddef.h> // size_t
#include <stdint.h> // uint8_t
#include <stdlib.h> // malloc()

#include "raylib.h"

// TODO: move this out of the box module
typedef struct Line {
  size_t cap;
  // This includes trailing NULL byte
  size_t len;
  uint8_t *data;
  // Negative means no cursor on this line
  int cursor;
  struct Line *next;
} Line;

typedef struct {
  Line *first;
  Line *current;
} Buffer;

Line *line_new();

// TODO: add from cursor, not len
void line_append(Line *buffer, size_t n, uint8_t data[static n]);

/// Inclusive start and ending indices of new buffer.
void line_resize(Line *buffer, size_t starting_index, size_t ending_index);

typedef struct {
  bool left_shift;
  // TODO: bool right_shift;
} KeyboardState;

// TODO: embed user state struct
struct _Window {
  Color color0;
  Color color2;
  Color color4;
  Font font;
  float font_height;
  float font_width;
  float screen_height;
  float screen_width;
  float padding;
  Buffer buffer;
  KeyboardState kbd_state;
};
typedef struct _Window *Window;

[[nodiscard]]
Window window_init(const char *font_path);

typedef Vector2 Constraints;
typedef Vector2 Size;

typedef enum {
  widgetTypeBuffer,
  widgetTypeTxt,
} WidgetType;

typedef struct {
  WidgetType type;
  union {
    Buffer buffer;
    const char *txt;
  };
} Widget;

typedef struct {
  Size size;
  WidgetType type;
  union {
    Buffer buffer;
    const char *txt;
  };
} RenderTarget;

void render_target_dispose(RenderTarget *target);

Widget widget_of_buffer(Buffer buffer);
Widget widget_of_txt(const char *str);

RenderTarget widget_layout(Window win, Widget *widget, Constraints constraints);
void window_render(Window win, RenderTarget target, Vector2 top_left);

void window_dispose(Window _);

typedef void (*WindowRenderCallback)(Window);
typedef void (*UpdateStateCallback)(Window);

void window_render_loop(Window win, WindowRenderCallback r,
                        UpdateStateCallback u);

#endif // MONOREPO_SRC_TXT_INCLUDE_BOX_H
