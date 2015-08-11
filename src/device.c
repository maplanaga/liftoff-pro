#include "device.h"

void deviceSurfaceEventHandler(u8 type, u8 index, u8 value) {
  displaySetLed(MODE_DEVICE, index, C_DEVICE);
}