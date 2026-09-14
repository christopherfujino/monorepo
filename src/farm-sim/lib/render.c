#include <stdarg.h> // variadic function
#include <stdio.h>  // vprintf()
#include <stdlib.h> // malloc()

#include "globals.h"
#include "raylib.h"
#include "render.h"

void print(const char *format, ...) {
  constexpr size_t buflen = 100;
  constexpr int fontsize = 20;
  char buf[buflen];
  va_list args;

  va_start(args);
  vsnprintf(buf, buflen, format, args);
  DrawText(buf, 10, SCREEN_HEIGHT - fontsize * 2, fontsize, green);
  va_end(args);
}


struct _gameState {
  int fps;
};

GameState init() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flooboo");
  GameState state = malloc(sizeof(struct _gameState));
  *state = (struct _gameState){.fps = 30};
  SetTargetFPS(state->fps);

  return state;
}

// TODO: embed in ScreenHandle?
static Rectangle avatar = {
    .x = 5,
    .y = 5,
    .width = 25,
    .height = 25,
};

static Camera2D camera = {
    .offset =
        (Vector2){
            .x = SCREEN_WIDTH / 2.0f,
            .y = SCREEN_HEIGHT / 2.0f,
        },
    .target = (Vector2){.x = 0, .y = 0},
    .rotation = 0,
    .zoom = 1,
};

// TODO move to another module
static void handleInput(GameState state) {
  if (IsKeyDown(KEY_H)) {
    avatar.x -= AVATAR_SPEED / state->fps;
    if (avatar.x < 0) {
      avatar.x = 0;
    }
  }
  if (IsKeyDown(KEY_L)) {
    avatar.x += AVATAR_SPEED / state->fps;
    if (avatar.x > SCREEN_WIDTH - 1) {
      avatar.x = SCREEN_WIDTH - 1;
    }
  }
}

void render(GameState state) {
  while (!WindowShouldClose()) {
    handleInput(state);
    BeginDrawing();
    {
      ClearBackground(white);

      BeginMode2D(camera);
      {
        DrawRectangleGradientH(0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT, white, black);
        DrawRectangleRec(avatar, green);
      }
      EndMode2D();

      DrawFPS(10, 10);
    }
    print("Avatar(%0.1f, %0.1f)\n", avatar.x, avatar.y);

    EndDrawing();
  }
}
