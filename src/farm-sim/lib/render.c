#include <stdarg.h> // variadic function
#include <stdio.h>  // vprintf()
#include <stdlib.h> // malloc()

#include "globals.h"
#include "raylib.h"
#include "render.h"
#include "state.h"

static void print(const char *format, ...) {
  constexpr size_t buflen = 100;
  va_list args;
  char buf[buflen];

  va_start(args);
  vsnprintf(buf, buflen, format, args);
  DrawText(buf, 10, SCREEN_HEIGHT - 1 - fontsize * 2, fontsize, color3);
  va_end(args);
}

// TODO move to another module
static void handleInput(GameState *state) {
  if (IsKeyDown(KEY_H)) {
    state->avatar.x -= AVATAR_SPEED / state->fps;
    if (state->avatar.x < 0) {
      state->avatar.x = 0;
    }
  }
  if (IsKeyDown(KEY_J)) {
    state->avatar.y += AVATAR_SPEED / state->fps;
    if (state->avatar.y > WORLD_HEIGHT - state->avatar.height) {
      state->avatar.y = WORLD_HEIGHT - state->avatar.height;
    }
  }
  if (IsKeyDown(KEY_K)) {
    state->avatar.y -= AVATAR_SPEED / state->fps;
    if (state->avatar.y < 0) {
      state->avatar.y = 0;
    }
  }
  if (IsKeyDown(KEY_L)) {
    state->avatar.x += AVATAR_SPEED / state->fps;
    if (state->avatar.x > WORLD_WIDTH - state->avatar.width) {
      state->avatar.x = WORLD_WIDTH - state->avatar.width;
    }
  }
  state->camera.target.x = state->avatar.x;
  state->camera.target.y = state->avatar.y;
}

void render(GameState *state) {
  while (!WindowShouldClose()) {
    handleInput(state);
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
}
