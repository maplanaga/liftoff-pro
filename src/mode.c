#include "mode.h"

u8 currentMode = MODE_SESSION;

void modeHasChangedHandler() {
  displaySetActiveBuffer(currentMode);
}

void modeSurfaceEventHandler(u8 type, u8 index, u8 value) {
  if(value > 0) {
    if(index == 95) {
      currentMode = MODE_SESSION;
    } else if (index == 96 && currentMode != MODE_PERFORM) {
      currentMode = MODE_PERFORM;
    } else if (index == 96 && currentMode == MODE_PERFORM) {
      currentMode = MODE_SEQ;
    } else if (index == 97) {
      currentMode = MODE_DEVICE;
    } else if (index == 98) {
      currentMode = MODE_USER;
    }
    modeHasChangedHandler();
  }
}

u8 modeGetCurrent() {
  return currentMode;
}