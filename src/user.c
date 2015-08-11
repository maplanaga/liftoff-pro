#include "user.h"

void userSurfaceEventHandler(u8 type, u8 index, u8 value) {
  displaySetLed(MODE_USER, index, C_USER);
}