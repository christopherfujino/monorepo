#include <stdio.h>

#include "box.h"
#include "raylib.h"

void my_render(Window win) {
  Widget root = widget_of_buffer(win->buffer);
  window_render(win,
                widget_layout(win, &root,
                              (Constraints){
                                  .x = win->screen_width,
                                  .y = win->screen_height,
                              }),
                (Vector2){.x = 0, .y = 0});
}

static inline bool _check_key(int key) {
  return IsKeyPressed(key) || IsKeyPressedRepeat(key);
}

typedef struct {
  char lower;
  char upper;
} CharTuple;

// These are printable symbols
constexpr CharTuple symbol_lookup[] = {
    [KEY_SPACE] = {' ', ' '},

    [KEY_APOSTROPHE] = {'\'', '"'},
    [KEY_COMMA] = {',', '<'},
    [KEY_MINUS] = {'-', '_'},
    [KEY_PERIOD] = {'.', '>'},
    [KEY_SLASH] = {'/', '?'},
    [KEY_ZERO] = {'0', ')'},
    [KEY_ONE] = {'1', '!'},
    [KEY_TWO] = {'2', '@'},
    [KEY_THREE] = {'3', '#'},
    [KEY_FOUR] = {'4', '$'},
    [KEY_FIVE] = {'5', '%'},
    [KEY_SIX] = {'6', '^'},
    [KEY_SEVEN] = {'7', '&'},
    [KEY_EIGHT] = {'8', '*'},
    [KEY_NINE] = {'9', '('},
    [KEY_SEMICOLON] = {';', ':'},
    [KEY_EQUAL] = {'=', '+'},

    [KEY_A] = {'a', 'A'},
    [KEY_B] = {'b', 'B'},
    [KEY_C] = {'c', 'C'},
    [KEY_D] = {'d', 'D'},
    [KEY_E] = {'e', 'E'},
    [KEY_F] = {'f', 'F'},
    [KEY_G] = {'g', 'G'},
    [KEY_H] = {'h', 'H'},
    [KEY_I] = {'i', 'I'},
    [KEY_J] = {'j', 'J'},
    [KEY_K] = {'k', 'K'},
    [KEY_L] = {'l', 'L'},
    [KEY_M] = {'m', 'M'},
    [KEY_N] = {'n', 'N'},
    [KEY_O] = {'o', 'O'},
    [KEY_P] = {'p', 'P'},
    [KEY_Q] = {'q', 'Q'},
    [KEY_R] = {'r', 'R'},
    [KEY_S] = {'s', 'S'},
    [KEY_T] = {'t', 'T'},
    [KEY_U] = {'u', 'U'},
    [KEY_V] = {'v', 'V'},
    [KEY_W] = {'w', 'W'},
    [KEY_X] = {'x', 'X'},
    [KEY_Y] = {'y', 'Y'},
    [KEY_Z] = {'z', 'Z'},

    [KEY_LEFT_BRACKET] = {'[', '{'},
    [KEY_BACKSLASH] = {'\\', '|'},
    [KEY_RIGHT_BRACKET] = {']', '}'},
    [KEY_GRAVE] = {'`', '~'},
    // TODO: parse this when rendering
    [KEY_TAB] = {'\t', '\t'},
};

void update_state(Window win) {
  if (IsKeyDown(KEY_LEFT_SHIFT)) {
    win->kbd_state.left_shift = true;
  }
  if (win->kbd_state.left_shift && IsKeyReleased(KEY_LEFT_SHIFT)) {
    win->kbd_state.left_shift = false;
  }
  size_t lookup_size = sizeof(symbol_lookup) / sizeof(CharTuple);
  for (unsigned int i = 0; i < lookup_size; i++) {
    CharTuple tuple = symbol_lookup[i];
    if (tuple.lower == '\0') {
      continue;
    }
    if (_check_key(i)) {
      uint8_t ch = win->kbd_state.left_shift ? tuple.upper : tuple.lower;
      line_append(win->buffer.current, 1, &ch);
      fputc(ch, stdout);
      fflush(stdout);
    }
  }

  if (_check_key(KEY_ENTER)) {
    Line *next = nullptr;
    if (win->buffer.current->next != nullptr) {
      next = win->buffer.current->next;
    }
    Line *current = line_new();
    // Allow previous line to point to newly created line
    win->buffer.current->next = current;
    // Update buffer to point to newly created line
    win->buffer.current = current;
    // Have newly created line point to the original next, if it exists
    win->buffer.current->next = next;

    fputc('\n', stdout);
    fflush(stdout);
  }

  if (_check_key(KEY_BACKSPACE)) {
    if (win->buffer.current->len > 0) {
      // TODO: hmm, why minus 2?
      line_resize(win->buffer.current, 0, win->buffer.current->len - 2);
    } else {
      Line *next = win->buffer.current->next;
      Line *previous =
          buffer_get_previous_line(&win->buffer, win->buffer.current);
      if (previous != nullptr) {
        win->buffer.current = line_dispose(win->buffer.current);
        win->buffer.current = previous;
        win->buffer.current->next = next;
      }
    }
  }

  // TODO: whitespace
  // KEY_TAB, KEY_ENTER
  // TODO: keypad? (KEY_KEP_0, et al)
  // TODO: handle right shift
}

int main() {
  Window win = window_init("../../3p/fonts/mononoki/mononoki-spritesheet.fnt");
  window_render_loop(win, my_render, update_state);
  window_dispose(win);

  return 0;
}
