#include "render.h"
#include "raylib.h"

struct _screenHandle {
  unsigned char _opaque;
};

ScreenHandle init() {
  InitWindow(width, height, "Flooboo");
  SetTargetFPS(30);

  return (ScreenHandle){};
}

// TODO: embed in ScreenHandle?
static Rectangle avatar = {
    .x = 5,
    .y = 5,
    .width = 25,
    .height = 25,
};

static Camera2D camera = (Camera2D){
    .offset = (Vector2){.x = width / 2.0f, .y = height / 2.0f},
    .target = (Vector2){.x = 0, .y = 0},
    .rotation = 0,
    .zoom = 1,
};

// TODO move to another module
static void handleInput() {
  if (IsKeyDown(KEY_H)) {
    avatar.x -= 1;
  }
  if (IsKeyDown(KEY_L)) {
    avatar.x += 1;
  }
}

void render(ScreenHandle) {
  while (!WindowShouldClose()) {
    handleInput();
    BeginDrawing();
    {
      ClearBackground(white);

      BeginMode2D(camera);
      {
        DrawRectangleRec(avatar, green);
      }
      EndMode2D();

      DrawFPS(10, 10);
    }
    EndDrawing();
  }
}
