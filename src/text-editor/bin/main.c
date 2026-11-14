#include "box.h"
#include "raylib.h"

// Does this need to be a function?
// Probably since we want to use state to conditionally describe widget tree.
// Use functional style state passing?
// Or can we just use static state?
// Functional style better for testing?
void my_render(Window win) {
  Widget root = widget_of_txt("Hello, world!");
  window_render(win,
                widget_layout(win, &root,
                              (Constraints){
                                  .x = win->screen_width,
                                  .y = win->screen_height,
                              }),
                (Vector2){.x = 0, .y = 0});
}

void update_state(Window win) {

}

int main() {
  Window win = window_init();
  window_render_loop(win, my_render, update_state);
  window_dispose(win);

  return 0;
}
