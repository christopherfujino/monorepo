#include <stdarg.h> // variadic function
#include <stdio.h>  // vprintf()
#include <stdlib.h> // malloc()

#include "globals.h"
#include "raylib.h"
#include "render.h"
#include "state.h"

constexpr Color color0 = (Color){0x14, 0x1F, 0x2C, 0xFF};
// constexpr Color color1 = (Color){0x3A, 0x58, 0x7F, 0xFF};
// constexpr Color color2 = (Color){0x56, 0x82, 0xBB, 0xFF};
constexpr Color color3 = (Color){0x70, 0xA9, 0xF3, 0xFF};

constexpr int fontsize = 20;

static void print(const char *format, ...) {
  constexpr size_t buflen = 100;
  va_list args;
  char buf[buflen];

  va_start(args);
  vsnprintf(buf, buflen, format, args);
  DrawText(buf, 10, SCREEN_HEIGHT - 1 - fontsize * 2, fontsize, color3);
  va_end(args);
}

void render(GameState *state) {
  BeginDrawing();
  {
    ClearBackground(color0);

    BeginMode2D(state->camera);
    {
      DrawTextureRec(state->mapTexture, state->mapRect, (Vector2){0, 0},
                     color3);
      DrawRectangleRec(state->avatar, color3);
    }
    EndMode2D();

    DrawFPS(SCREEN_WIDTH - 1 - fontsize * 10, SCREEN_HEIGHT - 1 - fontsize * 2);
  }
  print("Avatar(%0.1f, %0.1f)\n", state->avatar.x, state->avatar.y);

  EndDrawing();
}
