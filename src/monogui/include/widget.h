#ifndef __MONOREPO_SRC_MONOGUI_INCLUDE_WIDGET_H
#define __MONOREPO_SRC_MONOGUI_INCLUDE_WIDGET_H

typedef struct {
  enum { widget_text } tag;
  union {
    const char *text;
  };
} Widget;

static inline Widget widget_text_new(const char *s) {
  return (Widget){
      .tag = widget_text,
      .text = s,
  };
}

#endif // __MONOREPO_SRC_MONOGUI_INCLUDE_WIDGET_H
