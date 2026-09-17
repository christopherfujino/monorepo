#include <stdarg.h>    // variadic function
#include <stdatomic.h> // atomic_int
#include <stdio.h>     // vprintf()
#include <stdlib.h>    // malloc()
#include <string.h>    // strncpy()

#include "globals.h"
#include "raylib.h"
#include "render.h"
#include "state.h"

void print(const char *format, ...) {
  constexpr size_t buflen = 100;
  va_list args;
  char buf[buflen];

  va_start(args);
  vsnprintf(buf, buflen, format, args);
  DrawText(buf, 10, SCREEN_HEIGHT - 1 - FONTSIZE * 2, FONTSIZE, color3);
  va_end(args);
}

static inline void drawAnimation(Animation *animation, Rectangle destRect) {
  // DrawTexture(animation->texture, destRect.x, destRect.y, (Color){0xFF, 0xFF,
  // 0xFF, 0xFF});
  auto srcRect = (Rectangle){
      .x = animation->frameIndex * destRect.width,
      .y = 0,
      .height = destRect.height,
      .width = destRect.width,
  };
  DrawTexturePro(animation->texture, srcRect, destRect, (Vector2){0, 0}, 0,
                 WHITE);
}

void render(GameState *state) {
  BeginDrawing();
  {
    ClearBackground(color0);

    BeginMode2D(state->camera);
    {
      DrawTextureRec(state->mapTexture, state->mapRect, (Vector2){0, 0},
                     color3);
      drawAnimation(&state->avatar.idleAnimation, state->avatar.destRect);
    }
    EndMode2D();

    DrawFPS(SCREEN_WIDTH - 1 - FONTSIZE * 10, SCREEN_HEIGHT - 1 - FONTSIZE * 2);
  }
  print("Avatar(%0.1f, %0.1f)\n", state->avatar.destRect.x,
        state->avatar.destRect.y);

  EndDrawing();
}

int renderLoadingScreen(GameState *state, atomic_int *isDone) {
  constexpr int fps = 15;
  int retval = -1;

  const char msg[] = "Loading...";
  char buf[sizeof(msg)] = {0};
  SetTargetFPS(fps);

  unsigned int i = 0;
  while (!WindowShouldClose()) {
    if (atomic_load(isDone)) {
      retval = 1;
      goto end;
    }
    strncpy(buf, msg, i);
    buf[i] = '\0';

    BeginDrawing();
    {
      ClearBackground(color0);
      DrawText(buf, SCREEN_WIDTH / 2 - (FONTSIZE * 2), SCREEN_HEIGHT / 2 - 20,
               FONTSIZE * 2, color3);
    }
    EndDrawing();
    i += 1;
    if (i == sizeof(msg)) {
      i = 0;
    }
  }
  retval = 0;

end:
  SetTargetFPS(state->fps);
  return retval;
}
