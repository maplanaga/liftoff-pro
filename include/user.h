#ifndef __user_h__
#define __user_h__

#include "app_defs.h"
#include "display.h"

void userInit();
void userPadEventHandler(u8 index, u8 value);
void userButtonEventHandler(u8 index, bool value);

#endif