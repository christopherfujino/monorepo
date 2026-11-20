#include <ctype.h>

#include "box.h"
#include "common.h"
#include "raylib.h"

void my_render(Window win) {
  Widget root = widget_of_txt((char *)win->buffer.data);
  window_render(win,
                widget_layout(win, &root,
                              (Constraints){
                                  .x = win->screen_width,
                                  .y = win->screen_height,
                              }),
                (Vector2){.x = 0, .y = 0});
}

void update_state([[maybe_unused]] Window win) {
  int key = 0;
  uint8_t byte = 0;
  while ((key = GetKeyPressed()) != 0) {
    if (key <= 127) {
      byte = (uint8_t)key;
      uint8_t ch = win->kbd_state.shift ? byte : tolower(byte);
      buffer_add(&win->buffer, 1, &ch);
      fputc(key, stdout);
      fflush(stdout);
    } else {
      switch (key) {
      case KEY_BACKSPACE:
        if (win->buffer.len > 0) {
          buffer_resize(&win->buffer, 0, win->buffer.len - 2);
        }
        break;
      case KEY_LEFT_SHIFT:
      case KEY_RIGHT_SHIFT:
        // TODO: handle matrix of permutations
        printf("key shift\n");
        break;
      default:
        debug("key = %c (%d) [%s]\n", key, key, GetKeyName(key));
      }
    }
  }
}

int main() {
  Window win = window_init("../../3p/fonts/mononoki/mononoki-spritesheet.fnt");
  window_render_loop(win, my_render, update_state);
  window_dispose(win);

  return 0;
}
