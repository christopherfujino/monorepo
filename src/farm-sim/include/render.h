#ifndef __MONOREPO_SRC_FARMSIM_INCLUDE_RENDER_H
#define __MONOREPO_SRC_FARMSIM_INCLUDE_RENDER_H

#include "raylib.h"

struct _gameState;
typedef struct _gameState* GameState;

constexpr Color black = (Color){0, 0, 0, 0xFF};
constexpr Color white = (Color){0xFF, 0xFF, 0xFF, 0xFF};
constexpr Color green = (Color){
    .r = 0x80,
    .g = 0xFF,
    .b = 0x80,
    .a = 0xFF,
};

//typedef struct Object {
//  float x;
//  float y;
//  float dx;
//  float dy;
//} Object;

void render(GameState);
GameState init();

#endif // __MONOREPO_SRC_FARMSIM_INCLUDE_RENDER_H
