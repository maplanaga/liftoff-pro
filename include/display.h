#ifndef __device_h__
#define __device_h__

#include "app_defs.h"
#include "display.h"

void displaySetActiveBuffer(u8 buffer);

void displaySetLed(u8 index, u32 color);
void displaySetPad(u8 buffer, u8 index, u32 color);
void displaySetButton(u8 index, u32 color);
void displayClearPads(u8 buffer);
void displaySetPadXY(u8 buffer, u8 column, u8 row, u32 color);
u32 displayGetRandomColor();

#endif