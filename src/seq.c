#include "seq.h"

u8 step = 0;
bool pattern[8][8];

void seqSurfaceEventHandler(u8 type, u8 index, u8 value) {
  if(value > 0) {
    displaySetLed(MODE_SEQ, index, C_SEQ);
    pattern[(index%10) - 1][(index/10) - 1] = !pattern[(index%10) - 1][(index/10) - 1];
    if(pattern[(index%10) - 1][(index/10) - 1]){
      displaySetLed(MODE_SEQ, index, C_SEQ);
    } else {
      displaySetLed(MODE_SEQ, index, C_OFF);
    }
  }
}

void seqTimerEventHandler() {
  #define TICK_MS 200

  static u8 ms = TICK_MS;

  if (++ms >= TICK_MS)
  {
    ms = 0;

    step = (step + 1) % 8;
    for(u8 i = 0; i < 8; i++) {
      if(pattern[step][i]) {
        midiPlayNoteDirect(i + 36, 127);
      }
    }
    displaySetLed(MODE_SEQ, 1 + step, C_BLUE);
    displaySetLed(MODE_SEQ, step == 0 ? 8 : step, C_OFF);
  }
}