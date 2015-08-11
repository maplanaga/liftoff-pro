#ifndef __session_h__
#define __session_h__

#include "app_defs.h"
#include "display.h"

void sessionSurfaceEventHandler(u8 type, u8 index, u8 value);
void sessionSetForeground();
void sessionSetBackground();

#endif