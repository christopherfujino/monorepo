#ifndef __MONOREPO_SRC_MONOGUI_INCLUDE_RENDER_H
#define __MONOREPO_SRC_MONOGUI_INCLUDE_RENDER_H

#include "raylib.h"
#include "widget.h"

struct _RenderState;
typedef struct _RenderState *RenderState;

constexpr Color color0 = (Color){
    .r = 0,
    .g = 0,
    .b = 0,
    .a = 0xFF,
};

RenderState render_state_new();
void render_state_dispose(RenderState);

void render(RenderState, Widget);

#endif // __MONOREPO_SRC_MONOGUI_INCLUDE_RENDER_H
