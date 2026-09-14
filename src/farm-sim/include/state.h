#ifndef __MONOREPO_SRC_FARMSIM_INCLUDE_STATE_H
#define __MONOREPO_SRC_FARMSIM_INCLUDE_STATE_H

#include "raylib.h"

typedef struct GameState {
  int fps;
  Camera2D camera;
  Rectangle avatar;
  Texture2D mapTexture;
  Rectangle mapRect;
} GameState;

GameState *gameStateInit();
void gameStateDispose(GameState *);

#endif // __MONOREPO_SRC_FARMSIM_INCLUDE_STATE_H
