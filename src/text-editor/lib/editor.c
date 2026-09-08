#include "editor.h"

Editor editor_new(void) {
  return (Editor){
      .buffer = nullptr,
  };
}
