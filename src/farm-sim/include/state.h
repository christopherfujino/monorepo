#ifndef __MONOREPO_SRC_FARMSIM_INCLUDE_STATE_H
#define __MONOREPO_SRC_FARMSIM_INCLUDE_STATE_H

#include <stddef.h> // size_t
#include <stdint.h> // uint8_t

#include "raylib.h"

typedef struct Animation {
  Texture2D texture;
  uint8_t frameCount;
  uint8_t frameIndex;
  float frameLength;

  /** Elapsed time current frame has shown */
  float dt;
} Animation;

typedef struct Avatar {
  enum : uint8_t {
    avatarAnimationIdle,
  } animationType;
  Animation idleAnimation;

  Rectangle destRect;
} Avatar;

typedef struct GameState {
  int fps;
  Camera2D camera;
  Texture2D mapTexture;
  Rectangle mapRect;
  Avatar avatar;
} GameState;

GameState *gameStateInit();
void gameStateDispose(GameState *);

#endif // __MONOREPO_SRC_FARMSIM_INCLUDE_STATE_H
