#ifndef __perform_h__
#define __perform_h__

#include "app_defs.h"
#include "display.h"

void performInit();
void performSurfaceEventHandler(u8 type, u8 index, u8 value);
void performAftertouchEventHandler(u8 index, u8 value);

#endif