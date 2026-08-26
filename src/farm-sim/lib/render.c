#include "raylib.h"

constexpr Color black = (Color){};
constexpr Color green = (Color){
    .r = 0x80,
    .g = 0xFF,
    .b = 0x80,
    .a = 0xFF,
};

void render(void) {
  InitWindow(160, 90, "Flooboo");
  SetTargetFPS(30);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(black);
    DrawCircle(80, 45, 10.0, green);

    DrawFPS(10, 10);

    EndDrawing();
  }
}
