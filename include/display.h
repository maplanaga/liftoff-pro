#ifndef __device_h__
#define __device_h__

#include "app_defs.h"
#include "display.h"

void displaySetActiveBuffer(u8 buffer);

void displaySetLed(u8 buffer, u8 index, u32 color);

#endif