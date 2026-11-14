#ifndef MONOREPO_SRC_TXT_INCLUDE_BOX_H
#define MONOREPO_SRC_TXT_INCLUDE_BOX_H

#include <stddef.h> // size_t
#include <stdint.h> // uint8_t

#include "raylib.h"

// TODO: move this out of the box module
typedef struct {
  size_t cap;
  // This includes trailing NULL byte
  size_t len;
  uint8_t *data;
} Buffer;

void buffer_add(Buffer *buffer, size_t n, uint8_t data[static n]);

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
};
typedef struct _Window *Window;

[[nodiscard]]
Window window_init(const char *font_path);

typedef Vector2 Constraints;
typedef Vector2 Size;

typedef enum {
  widgetTypeTxt,
} WidgetType;

typedef struct {
  WidgetType type;
  union {
    const char *txt;
  };
} Widget;

typedef struct {
  Size size;
  WidgetType type;
  union {
    struct {
      const char *str;
    } txt;
  };
} RenderTarget;

/// Copies [string] but does not free it.
Widget widget_of_txt(const char *string);

RenderTarget widget_layout(Window win, Widget *widget, Constraints constraints);
void window_render(Window win, RenderTarget target, Vector2 top_left);

void window_dispose(Window _);

typedef void (*WindowRenderCallback)(Window);
typedef void (*UpdateStateCallback)(Window);

void window_render_loop(Window win, WindowRenderCallback r,
                        UpdateStateCallback u);

#endif // MONOREPO_SRC_TXT_INCLUDE_BOX_H
