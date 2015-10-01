#ifndef __perform_h__
#define __perform_h__

#include "app_defs.h"
#include "display.h"
#include "midi.h"
#include "core.h"

void performInit();
void performPadEventHandler(u8 index, u8 value);
void performButtonEventHandler(u8 index, bool value);
void performAftertouchEventHandler(u8 index, u8 value);
void performMidiInEventHandler(u8 status, u8 d1, u8 d2);

#endif