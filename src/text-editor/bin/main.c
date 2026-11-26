#include <ctype.h>
#include <stdio.h>

#include "box.h"
#include "common.h" // debug()
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
    [KEY_SPACE] = (CharTuple){' ', ' '},

    [KEY_APOSTROPHE] = (CharTuple){'\'', '"'},
    [KEY_COMMA] = (CharTuple){',', '<'},
    [KEY_MINUS] = (CharTuple){'-', '_'},
    [KEY_PERIOD] = (CharTuple){'.', '>'},
    [KEY_SLASH] = (CharTuple){'/', '?'},
    [KEY_ZERO] = (CharTuple){'0', ')'},
    [KEY_ONE] = (CharTuple){'1', '!'},
    [KEY_TWO] = (CharTuple){'2', '@'},
    [KEY_THREE] = (CharTuple){'3', '#'},
    [KEY_FOUR] = (CharTuple){'4', '$'},
    [KEY_FIVE] = (CharTuple){'5', '%'},
    [KEY_SIX] = (CharTuple){'6', '^'},
    [KEY_SEVEN] = (CharTuple){'7', '&'},
    [KEY_EIGHT] = (CharTuple){'8', '*'},
    [KEY_NINE] = (CharTuple){'9', '('},
    [KEY_SEMICOLON] = (CharTuple){';', ':'},
    [KEY_EQUAL] = (CharTuple){'=', '+'},

    [KEY_LEFT_BRACKET] = (CharTuple){'[', '{'},
    [KEY_BACKSLASH] = (CharTuple){'\\', '|'},
    [KEY_RIGHT_BRACKET] = (CharTuple){']', '}'},
    [KEY_GRAVE] = (CharTuple){'`', '~'},
    // TODO: parse this when rendering
    [KEY_TAB] = (CharTuple){'\t', '\t'},
};

void update_state(Window win) {
  if (IsKeyDown(KEY_LEFT_SHIFT)) {
    win->kbd_state.left_shift = true;
  }
  if (win->kbd_state.left_shift && IsKeyReleased(KEY_LEFT_SHIFT)) {
    win->kbd_state.left_shift = false;
  }
  // TODO: delete in favor of lower loop
  for (uint8_t current_key = KEY_A; current_key <= KEY_Z; current_key++) {
    if (_check_key(current_key)) {
      uint8_t ch =
          win->kbd_state.left_shift ? current_key : tolower(current_key);
      line_append(win->buffer.current, 1, &ch);
      fputc(ch, stdout);
      fflush(stdout);
    }
  }

  size_t lookup_size = sizeof(symbol_lookup) / sizeof(CharTuple);
  for (unsigned int i = 0; i < lookup_size; i++) {
    CharTuple tuple = symbol_lookup[i];
    if (tuple.lower == '\0') {
      debug("Skipping code 0x%02X\n", i);
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
