#ifndef __seq_h__
#define __seq_h__

#include "app_defs.h"
#include "display.h"
#include "midi.h"

void seqSurfaceEventHandler(u8 type, u8 index, u8 value);
void seqTimerEventHandler();
void seqInit();

#endif