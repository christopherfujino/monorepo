// #include "mod1.h"
#include "raylib.h"
#include <stdio.h>

constexpr Color black = (Color){};
constexpr Color green = (Color){
    .r = 0x80,
    .g = 0xFF,
    .b = 0x80,
    .a = 0xFF,
};

constexpr int width = 320;
constexpr int height = 180;
constexpr int fps = 60;
constexpr float radius = 10.0;

typedef struct State {
  Vector2 avatarPos;
} State;

static void checkInput(State *s) {
  if (IsKeyDown(KEY_H)) {
    s->avatarPos.x -= 1;
    // TODO compare edge, not center
    if (s->avatarPos.x < 0) {
      s->avatarPos.x = 0;
    }
  }
  if (IsKeyDown(KEY_J)) {
    s->avatarPos.y += 1;
    if (s->avatarPos.y >= height) {
      s->avatarPos.y = height - 1;
    }
  }
  if (IsKeyDown(KEY_K)) {
    s->avatarPos.y -= 1;
    if (s->avatarPos.y < 0) {
      s->avatarPos.y = 0;
    }
  }
  if (IsKeyDown(KEY_L)) {
    s->avatarPos.x += 1;
    if (s->avatarPos.x >= width) {
      s->avatarPos.x = width - 1;
    }
  }
}

int main(void) {
  State state = (State){
      .avatarPos =
          (Vector2){
              .x = (float)width / 2,
              .y = (float)height / 2,
          },
  };
  InitWindow(width, height, "Flooboo");
  SetTargetFPS(fps);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(black);
    checkInput(&state);
    DrawCircle((int)state.avatarPos.x, (int)state.avatarPos.y, radius, green);

    DrawFPS(10, 10);

    EndDrawing();
  }

  return 0;
}
