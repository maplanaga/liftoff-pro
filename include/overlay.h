#ifndef __overlay_h__
#define __overlay_h__

#include "app_defs.h"
#include "core.h"
#include "display.h"

void overlayInit();
void overlaySwitch(u8 index);
void overlayPadEventHandler(u8 index, u8 value);


#endif