#ifndef __MONOREPO_SRC_FARMSIM_INCLUDE_RENDER_H
#define __MONOREPO_SRC_FARMSIM_INCLUDE_RENDER_H

#include "raylib.h"

struct _gameState;
typedef struct _gameState *GameState;

constexpr Color color0 = (Color){.r = 0x14, .g = 0x1f, .b = 0x2c, .a = 0xFF};
constexpr Color color1 = (Color){.r = 0x3a, .g = 0x58, .b = 0x7f, .a = 0xFF};
constexpr Color color2 = (Color){.r = 0x56, .g = 0x82, .b = 0xbb, .a = 0xFF};
constexpr Color color3 = (Color){.r = 0x70, .g = 0xa9, .b = 0xf3, .a = 0xFF};

constexpr int fontsize = 20;

void render(GameState);
GameState gameStateInit();
void gameStateDispose(GameState);

#endif // __MONOREPO_SRC_FARMSIM_INCLUDE_RENDER_H
