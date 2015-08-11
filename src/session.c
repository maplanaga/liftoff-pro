#include "session.h"

void sessionSurfaceEventHandler(u8 type, u8 index, u8 value) {
  displaySetLed(MODE_SESSION, index, C_SESSION);
}