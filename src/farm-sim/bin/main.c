// #include "mod1.h"
#include "raylib.h"
// #include <stdio.h>

constexpr Color black = (Color){};
constexpr Color green = (Color){
    .r = 0x80,
    .g = 0xFF,
    .b = 0x80,
    .a = 0xFF,
};

int main(void) {
  // printf("The answer is %d.\n", mod1());

  InitWindow(160, 90, "Flooboo");
  SetTargetFPS(30);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(black);
    DrawCircle(80, 45, 10.0, green);

    DrawFPS(10, 10);

    EndDrawing();
  }

  return 0;
}
