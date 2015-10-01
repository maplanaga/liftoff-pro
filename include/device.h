#ifndef __device_h__
#define __device_h__

#include "app_defs.h"
#include "display.h"

void deviceInit();
void devicePadEventHandler(u8 index, u8 value);
void deviceButtonEventHandler(u8 index, bool value);

#endif