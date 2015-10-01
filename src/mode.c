#include "mode.h"

u8 currentMode = MODE_SESSION;
bool overlayActive = false;

void modeHasChangedHandler() {
  displaySetActiveBuffer(currentMode);
}

void modeButtonEventHandler(u8 index, bool value) {
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

void modeOverlayEventHandler(u8 index, bool value) {
  if(value) {
    displaySetActiveBuffer(MODE_OVERLAY);
    overlaySwitch(index);
    overlayActive = true;
  } else {
    displaySetActiveBuffer(currentMode);
    overlayActive = false;
  }
}

u8 modeGetCurrent() {
  if(!overlayActive) {
    return currentMode;
  } else {
    return MODE_OVERLAY;
  }
}