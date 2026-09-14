#include <stdarg.h> // variadic function
#include <stdio.h>  // vprintf()
#include <stdlib.h> // malloc()

#include "globals.h"
#include "raylib.h"
#include "render.h"

static void print(const char *format, ...) {
  constexpr size_t buflen = 100;
  va_list args;
  char buf[buflen];

  va_start(args);
  vsnprintf(buf, buflen, format, args);
  DrawText(buf, 10, SCREEN_HEIGHT - 1 - fontsize * 2, fontsize, color3);
  va_end(args);
}

struct _gameState {
  int fps;
  Camera2D camera;
  Rectangle avatar;
  Texture2D mapTexture;
  Rectangle mapRect;
};

GameState gameStateInit() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flooboo");
  GameState state = malloc(sizeof(struct _gameState));
  {
    auto mapImage =
        GenImagePerlinNoise(SCREEN_WIDTH, SCREEN_HEIGHT, 40, 40, 2.0);
    state->mapTexture = LoadTextureFromImage(mapImage);
    UnloadImage(mapImage);
    state->mapRect = (Rectangle){
        .x = 0,
        .y = 0,
        .width = WORLD_WIDTH,
        .height = WORLD_HEIGHT,
    };
  }
  state->fps = FPS;
  SetTargetFPS(state->fps);
  state->camera = (Camera2D){
      .offset =
          (Vector2){
              .x = SCREEN_WIDTH / 2.0f,
              .y = SCREEN_HEIGHT / 2.0f,
          },
      .target = (Vector2){.x = 0, .y = 0},
      .rotation = 0,
      .zoom = 2,
  };
  state->avatar = (Rectangle){
      .x = 5,
      .y = 5,
      .width = 25,
      .height = 25,
  };

  return state;
}

void gameStateDispose(GameState state) {
  UnloadTexture(state->mapTexture);
  free(state);
}

// TODO move to another module
static void handleInput(GameState state) {
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

void render(GameState state) {
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
