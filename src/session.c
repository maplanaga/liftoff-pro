#include "session.h"


void drawChannels() {
  for(u8 i = 0; i < NUM_CHANNELS; i++) {
    for(u8 j = 0; j < 8; j++) {
      if(coreChannels[i].clips[j].filled) {
        displaySetPadXY(MODE_SESSION, i, j, coreChannels[i].color);
      } else {
        displaySetPadXY(MODE_SESSION, i, j, C_GREEN_1);
      }
    }
    displaySetPadXY(MODE_SESSION, i, coreChannels[i].playing, C_GREEN_4);
  }
}

void setPlaying(u8 index) {
  coreChannels[index % 8].playing = 7 - index / 8;
  drawChannels();
}

void sessionInit() {
  drawChannels();
}

void sessionPadEventHandler(u8 index, u8 value) {
  if(value > 0) {
    setPlaying(index);
  }
}

void sessionButtonEventHandler(u8 index, bool value) {

}