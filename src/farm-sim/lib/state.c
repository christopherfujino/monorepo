#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>  // perror()
#include <stdlib.h> // malloc()
#include <string.h> // memset(), strcpy()

#include "globals.h"
#include "map.h"
#include "render.h"
#include "state.h"

// TODO: Move to a long-lived worker thread?
static void *_syncLoad(void *voidIsDone) {
  atomic_int *isDone = voidIsDone;

  Image *image = calloc(1, sizeof(Image));
  image->data = MapData;
  if (image->data == nullptr) {
    atomic_store(isDone, 1);
    return nullptr;
  }
  image->width = MapWidth;
  image->height = MapHeight;
  image->format = MapFormat;
  image->mipmaps = 1;

  atomic_store(isDone, 1);
  return image;
}

GameState *gameStateInit() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flooboo");

  atomic_int loadDone;
  atomic_init(&loadDone, 0);
  pthread_t workerThread = 0;
  constexpr void *threadAttributes = nullptr;
  if (pthread_create(&workerThread, threadAttributes, _syncLoad, &loadDone) !=
      0) {
    perror("pthread_create() failed!");
    abort();
  }

  GameState *state = calloc(1, sizeof(GameState));
  state->fps = FPS;
  if (!renderLoadingScreen(state, &loadDone)) {
    abort();
  }
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
    if (!IsTextureValid(state->mapTexture)) {
      abort();
    }

    // Don't unload, memory is static!
    //UnloadImage(*image);
    free(image);
  }
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
  {
    constexpr size_t textureCount = 4;
    constexpr float avatarWidth = 25;
    constexpr float avatarHeight = 25;
    Texture2D texture;
    {

      auto image =
          GenImageColor(avatarWidth * textureCount, avatarHeight, color0);
      ImageDrawRectangle(&image, avatarWidth * 1, 0, avatarWidth, avatarHeight,
                         color1);
      ImageDrawRectangle(&image, avatarWidth * 2, 0, avatarWidth, avatarHeight,
                         color2);
      ImageDrawRectangle(&image, avatarWidth * 3, 0, avatarWidth, avatarHeight,
                         color3);
      texture = LoadTextureFromImage(image);
      if (!IsTextureValid(texture)) {
        abort();
      }
      UnloadImage(image);
    }
    state->avatar = (Avatar){
        .idleAnimation =
            (Animation){
                .texture = texture,
                .frameCount = textureCount,
                .frameIndex = 0,
                .frameLength = (float)textureCount * 2 / FPS,
            },
        .animationType = avatarAnimationIdle,
        .destRect =
            (Rectangle){
                .x = 5,
                .y = 5,
                .width = 25,
                .height = 25,
            },
    };
  }
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
