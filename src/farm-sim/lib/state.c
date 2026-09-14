#include "state.h"
#include "globals.h"
#include <stdlib.h>

GameState *gameStateInit() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flooboo");
  GameState *state = malloc(sizeof(GameState));
  {
    auto mapImage =
        GenImagePerlinNoise(WORLD_WIDTH, WORLD_HEIGHT, 5, 40, 100);
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

void gameStateDispose(GameState *state) {
  UnloadTexture(state->mapTexture);
  free(state);
}
