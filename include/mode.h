#ifndef __mode_h__
#define __mode_h__

#include "app_defs.h"
#include "display.h"

void modeSurfaceEventHandler(u8 type, u8 index, u8 value);

u8 modeGetCurrent();

#endif