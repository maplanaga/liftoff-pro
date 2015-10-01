#include "overlay.h"

u8 currentOverlay = BUTTON_RECORD_ARM;

void drawClipSelect() {
  for(u8 i = 0; i < NUM_CHANNELS; i++) {
    for(u8 j = 0; j < 8; j++) {
      if(coreChannels[i].clips[j].filled) {
        displaySetPadXY(MODE_OVERLAY, i, j, coreChannels[i].color);
      } else {
        displaySetPadXY(MODE_OVERLAY, i, j, C_GRAY_1);
      }
    }
  }
  displaySetPadXY(MODE_OVERLAY, coreGetCurrent(_CHANNEL), coreGetCurrent(_CLIP), C_WHITE);
}

void drawClipCreate() {
  for(u8 i = 0; i < NUM_CHANNELS; i++) {
    for(u8 j = 0; j < 8; j++) {
      if(coreChannels[i].clips[j].filled) {
        displaySetPadXY(MODE_OVERLAY, i, j, coreChannels[i].color);
      } else {
        displaySetPadXY(MODE_OVERLAY, i, j, C_RED_1);
      }
    }
  }
}

void selectClip(u8 index) {
  coreSetCurrent(_CHANNEL, index % 8);
  coreSetCurrent(_CLIP, 7 - index / 8);
  drawClipSelect();
  refreshButtonColors();
  app_clipchange_event();
}

void createClip(u8 index) {
  coreChannels[index % 8].clips[7 - index / 8].filled = true;
  drawClipCreate();
}

void drawMuteSelect() {
  for(u8 i = 0; i < NUM_CHANNELS; i++) {
    if(coreChannels[i].mute){
      displaySetPad(MODE_OVERLAY, i, C_BLUE_4);
    } else {
      displaySetPad(MODE_OVERLAY, i, C_BLUE_2);
    }
  }
}

void drawSoloSelect() {
  for(u8 i = 0; i < NUM_CHANNELS; i++) {
    if(coreChannels[i].solo){
      displaySetPad(MODE_OVERLAY, i, C_YELLOW_4);
    } else {
      displaySetPad(MODE_OVERLAY, i, C_YELLOW_2);
    }
  }
}

void setSolo(u8 index) {
  coreChannels[index].solo = !(bool)coreChannels[index].solo;
  drawSoloSelect();
  refreshButtonColors();
}

void setMute(u8 index) {
  coreChannels[index].mute = !(bool)coreChannels[index].mute;
  drawMuteSelect();
  refreshButtonColors();
}

void refreshButtonColors() {
  displaySetButton(BUTTON_RECORD_ARM, C_RED_1);
  displaySetButton(BUTTON_TRACK_SELECT, coreChannels[coreGetCurrent(_CHANNEL)].color);
  displaySetButton(BUTTON_MUTE, C_BLUE_1);
  displaySetButton(BUTTON_SOLO, C_YELLOW_1);
  displaySetButton(BUTTON_VOLUME, C_CYAN_1);
  displaySetButton(BUTTON_PAN, C_MAGENTA_1);
  displaySetButton(BUTTON_SENDS, C_MAGENTA_1);
  displaySetButton(BUTTON_STOP_CLIP, C_RED_1);

  for(u8 i = 0; i < NUM_CHANNELS; i++) {
    if(coreChannels[i].solo) {displaySetButton(BUTTON_SOLO, C_YELLOW_4);}
    if(coreChannels[i].mute) {displaySetButton(BUTTON_MUTE, C_BLUE_4);}
  }
}

void overlayPadEventHandler(u8 index, u8 value) {
  switch (currentOverlay) {
    case BUTTON_RECORD_ARM   : if(value > 0 && index % 8 < NUM_CHANNELS) {createClip(index);}break;
    case BUTTON_TRACK_SELECT : if(value > 0 && index % 8 < NUM_CHANNELS) {selectClip(index);} break;
    case BUTTON_MUTE         : if(value > 0 && index < NUM_CHANNELS) {setMute(index);} break;
    case BUTTON_SOLO         : if(value > 0 && index < NUM_CHANNELS) {setSolo(index);}break;
    case BUTTON_VOLUME       : break;
    case BUTTON_PAN          : break;
    case BUTTON_SENDS        : break;
    case BUTTON_STOP_CLIP    : break;
  }
}

void overlayInit() {
  refreshButtonColors();
}

void overlaySwitch(u8 index) {
  currentOverlay = index;
  displayClearPads(MODE_OVERLAY);
  switch (index) {
    case BUTTON_RECORD_ARM   : drawClipCreate(); break;
    case BUTTON_TRACK_SELECT : drawClipSelect(); break;
    case BUTTON_MUTE         : drawMuteSelect(); break;
    case BUTTON_SOLO         : drawSoloSelect(); break;
    case BUTTON_VOLUME       : displayClearPads(MODE_OVERLAY); break;
    case BUTTON_PAN          : displayClearPads(MODE_OVERLAY); break;
    case BUTTON_SENDS        : displayClearPads(MODE_OVERLAY); break;
    case BUTTON_STOP_CLIP    : displayClearPads(MODE_OVERLAY); break;
  }
}