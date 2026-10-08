#ifndef __MONOREPO_SRC_MONOGUI_INCLUDE_LAYOUT_H
#define __MONOREPO_SRC_MONOGUI_INCLUDE_LAYOUT_H

#include "common.h"
#include "raylib.h"
#include "widget.h"

typedef Vector2 Constraints;
typedef Vector2 Size;

typedef struct {
  Widget *widget;
  Size size;
} Element;

Result layout(Widget, Constraints, Element *);

#endif // __MONOREPO_SRC_MONOGUI_INCLUDE_LAYOUT_H
