#ifndef __MONOREPO_SRC_FARMSIM_INCLUDE_RENDER_H
#define __MONOREPO_SRC_FARMSIM_INCLUDE_RENDER_H

#include "raylib.h"

struct _screenHandle;
typedef struct _screenHandle* ScreenHandle;

constexpr Color black = (Color){0, 0, 0, 0xFF};
constexpr Color white = (Color){0xFF, 0xFF, 0xFF, 0xFF};
constexpr Color green = (Color){
    .r = 0x80,
    .g = 0xFF,
    .b = 0x80,
    .a = 0xFF,
};

constexpr int height = 600;
constexpr int width = 800;

void render(ScreenHandle);
ScreenHandle init();

#endif // __MONOREPO_SRC_FARMSIM_INCLUDE_RENDER_H
