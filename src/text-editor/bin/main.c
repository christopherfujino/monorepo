#include "box.h"
#include "chrislib.h"
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
      buffer_add(&win->buffer, 1, &byte);
      fputc(key, stdout);
      fflush(stdout);
    } else {
      switch (key) {
      case KEY_BACKSPACE:
        panic("TODO");
      default:
        debug("key = %c (%d)\n", key, key);
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
