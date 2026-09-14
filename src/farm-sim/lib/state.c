#include "state.h"
#include "globals.h"
#include "render.h"
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>  // perror()
#include <stdlib.h> // malloc()
#include <string.h> // strcpy()

static void *_syncLoad(void *voidIsDone) {
  atomic_int *isDone = voidIsDone;

  Image *image = malloc(sizeof(Image));
  *image = GenImagePerlinNoise(WORLD_WIDTH, WORLD_HEIGHT, 5, 40, 100);

  atomic_store(isDone, 1);
  return image;
}

GameState *gameStateInit() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flooboo");

  constexpr int fps = 15;
  SetTargetFPS(fps);

  atomic_int loadDone;
  atomic_init(&loadDone, 0);
  pthread_t workerThread = 0;
  constexpr void *threadAttributes = nullptr;
  if (pthread_create(&workerThread, threadAttributes, _syncLoad, &loadDone) !=
      0) {
    perror("pthread_create() failed!");
    abort();
  }

  char msg[] = "Loading...";
  char buf[sizeof(msg)] = {0};

  unsigned int i = 0;
  while (!WindowShouldClose()) {
    if (atomic_load(&loadDone)) {
      break;
    }
    {
      strncpy(buf, msg, i);
      buf[i] = '\0';
    }
    printf("DEBUG: %s %d\n", buf, i);

    BeginDrawing();
    {
      ClearBackground(color0);
      DrawText(buf, SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 - 20, fontsize * 2,
               color3);
    }
    EndDrawing();
    i += 1;
    if (i == sizeof(msg)) {
      i = 0;
    }
  }
  GameState *state = malloc(sizeof(GameState));
  {
    Image *image = nullptr;
    int err = pthread_join(workerThread, (void **)&image);
    if (err != 0) {
      perror("pthread_join() failed!");
      abort();
    }
    if (image == nullptr) {
      abort();
    }
    state->mapTexture = LoadTextureFromImage(*image);
    UnloadImage(*image);
    free(image);
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
  state->mapRect = (Rectangle){
      .x = 0,
      .y = 0,
      .width = WORLD_WIDTH,
      .height = WORLD_HEIGHT,
  };

  return state;
}

void gameStateDispose(GameState *state) {
  UnloadTexture(state->mapTexture);
  free(state);
}
