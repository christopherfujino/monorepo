#include <setjmp.h>
#include <string.h> // strlen()

#include "common.h"
#include "layout.h"

static inline Element _layoutText(jmp_buf j, const char *s, Constraints c) {
  size_t len = strlen(s);
  if (len > c.x) {
    longjmp(j, 1);
  }

  return (Element){
  };
}

static Element _layout(jmp_buf j, Widget w, Constraints c) {
  switch (w.tag) {
    case widget_text:
      return _layoutText(j, w.text, c);
  }
}

Result layout(Widget w, Constraints c, Element *e) {
  jmp_buf env;
  if (setjmp(env) == 0) {
    *e = _layout(env, w, c);
    return result_ok;
  } else {
    return result_err;
  }
}
