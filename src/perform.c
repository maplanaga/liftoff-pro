#include "perform.h"

void performSurfaceEventHandler(u8 type, u8 index, u8 value) {
  displaySetLed(MODE_PERFORM, index, C_PERFORM);
}

void performInit() {
}