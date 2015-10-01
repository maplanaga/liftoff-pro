#ifndef __core_h__
#define __core_h__

#include "app_defs.h"

#define _CHANNEL      0
#define _CLIP         1
#define _SCALE_TYPE   2
#define _OCTAVE       3
#define _ROOT_NOTE    4
#define _FOLDED       5
#define _FIXED        6
#define _ISO          7

struct clip {
  u8 scaleType;
  u8 octave;
  u8 rootNote;
  bool folded;
  bool fixed;
  bool iso;
  bool filled;
  u8 length;
  u8 steps[64][4];
};

struct channel {
  u32 color;
  bool solo;
  bool mute;
  u8 volume;
  u8 playing;
  u8 atStep;
  struct clip clips[8];
};

struct channel coreChannels[NUM_CHANNELS];

u8 coreGetCurrent(u8 type);
void coreSetCurrent(u8 type, u8 value);
void coreTimerEventHandler();

#endif