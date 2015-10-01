#ifndef __session_h__
#define __session_h__

#include "app_defs.h"
#include "display.h"
#include "core.h"

void sessionInit();
void sessionPadEventHandler(u8 index, u8 value);
void sessionButtonEventHandler(u8 index, bool value);

u8 sessionGetSelectedChannel();
u8 sessionGetSelectedPattern();

#endif