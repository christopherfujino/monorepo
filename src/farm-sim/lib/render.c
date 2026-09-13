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

void render(ScreenHandle) {
  Rectangle avatar = {
    .x = 5,
    .y = 5,
    .width = 25,
    .height = 25,
  };
  Camera2D camera = (Camera2D){
      .offset = (Vector2){.x = width / 2.0f, .y = height / 2.0f},
      .target = (Vector2){.x = 0, .y = 0},
      .rotation = 0,
      .zoom = 1,
  };

  while (!WindowShouldClose()) {
    BeginDrawing();
    {
      ClearBackground(white);

      BeginMode2D(camera);
      {
        DrawGrid(30, 5.0f);
        DrawRectangleRec(avatar, green);
      }
      EndMode2D();

      DrawFPS(10, 10);
    }
    EndDrawing();
  }
}
