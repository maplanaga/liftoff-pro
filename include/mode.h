#ifndef __mode_h__
#define __mode_h__

#include "app_defs.h"
#include "display.h"

void modeButtonEventHandler(u8 index, bool value);
void modeOverlayEventHandler(u8 index, bool value);

u8 modeGetCurrent();

#endif