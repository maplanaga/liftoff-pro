#include "device.h"

void deviceInit() {

}

void devicePadEventHandler(u8 index, u8 value) {
  displaySetPad(MODE_DEVICE, index, C_DEVICE);
}

void deviceButtonEventHandler(u8 index, bool value) {
  displaySetButton(index, C_DEVICE);
}