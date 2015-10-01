#ifndef __seq_h__
#define __seq_h__

#include "app_defs.h"
#include "display.h"
#include "midi.h"

void seqInit();
void seqPadEventHandler(u8 index, u8 value);
void seqButtonEventHandler(u8 index, bool value);
void seqTimerEventHandler();

#endif