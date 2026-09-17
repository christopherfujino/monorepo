#ifndef __MONOREPO_SRC_FARMSIM_INCLUDE_RENDER_H
#define __MONOREPO_SRC_FARMSIM_INCLUDE_RENDER_H

#include <stdatomic.h>

#include "state.h"

constexpr Color color0 = (Color){0x14, 0x1F, 0x2C, 0xFF};
constexpr Color color1 = (Color){0x3A, 0x58, 0x7F, 0xFF};
constexpr Color color2 = (Color){0x56, 0x82, 0xBB, 0xFF};
constexpr Color color3 = (Color){0x70, 0xA9, 0xF3, 0xFF};

constexpr int FONTSIZE = 20;

void print(const char *format, ...);
void render(GameState *);
int renderLoadingScreen(GameState *, atomic_int *);

#endif // __MONOREPO_SRC_FARMSIM_INCLUDE_RENDER_H
