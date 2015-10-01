#ifndef __midi_h__
#define __midi_h__

#include "app_defs.h"

void midiPlayNoteDirect(u8 channel, u8 index, u8 value);
void midiSendAftertouchDirect(u8 channel, u8 index, u8 value);

#endif