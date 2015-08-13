#include "seq.h"

u8 step = 0;
u8 channel = 0;
u8 pattern[8][8];
u8 drum[16][32];
u8 midiNoteOffset = 36;
/*
static const u8 lookupPad[100] = {
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0
};

static const u8 lookupMidiNote[128] = {
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0
};

*/

static const u8 lookupPadToMidiNote[100] = {
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  48  , 49  , 50  , 51  , 0   , 0   , 0   , 0   ,  0,
0    ,  44  , 45  , 46  , 47  , 0   , 0   , 0   , 0   ,  0,
0    ,  40  , 41  , 42  , 43  , 0   , 0   , 0   , 0   ,  0,
0    ,  36  , 37  , 38  , 39  , 0   , 0   , 0   , 0   ,  0,
0    ,  48  , 49  , 50  , 51  , 0   , 0   , 0   , 0   ,  0,
0    ,  44  , 45  , 46  , 47  , 0   , 0   , 0   , 0   ,  0,
0    ,  40  , 41  , 42  , 43  , 0   , 0   , 0   , 0   ,  0,
0    ,  36  , 37  , 38  , 39  , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0
};

static const u8 lookupMidiNoteToPad[128] = {
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 81  , 82  , 83 , 84,
71  , 72  , 73  , 74  , 61  , 62  , 63  , 64  , 51 , 52,
53  , 54   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 0,
0   , 0   , 0   , 0   , 0   , 0   , 0   , 0
};

static const u8 lookupPadToChannel[100] = {
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  12  , 13  , 14  , 15  , 0   , 0   , 0   , 0   ,  0,
0    ,  8   , 9   , 10  , 11  , 0   , 0   , 0   , 0   ,  0,
0    ,  4   , 5   , 6   , 7   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 1   , 2   , 3   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0
};

static const u8 lookupPadToStep[100] = {
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0,
0    ,  0   , 0   , 0   , 0   , 28  , 29  , 30  , 31  ,  0,
0    ,  0   , 0   , 0   , 0   , 24  , 25  , 26  , 27  ,  0,
0    ,  0   , 0   , 0   , 0   , 20  , 21  , 22  , 23  ,  0,
0    ,  0   , 0   , 0   , 0   , 16  , 17  , 18  , 19  ,  0,
0    ,  0   , 0   , 0   , 0   , 12  , 13  , 14  , 15  ,  0,
0    ,  0   , 0   , 0   , 0   , 8   , 9   , 10  , 11  ,  0,
0    ,  0   , 0   , 0   , 0   , 4   , 5   , 6   , 7   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 1   , 2   , 3   ,  0,
0    ,  0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,  0
};

static const u8 lookupStepToPad[32] = {
  85, 86, 87, 88,
  75, 76, 77, 78,
  65, 66, 67, 68,
  55, 56, 57, 58,
  45, 46, 47, 48,
  35, 36, 37, 38,
  25, 26, 27, 28,
  15, 16, 17, 18
};

void drawChannel(u8 channel) {
  u8 count = 0;
  for(u8 row = 8; row > 0; row--) {
    for(u8 cell = 5; cell <= 8; cell++) {
      u8 value = drum[channel][count];
      displaySetLed(MODE_SEQ, row * 10 + cell, (value<<16)+(value<<8)+value);
      if(count < 31){
        count++;
      } else {
        break;
      }
    }
  }
}


void drawPads() {
  for(u8 i = 50; i < 90; i++) {
    if(i % 10 >= 1 && i % 10 <= 4) {
      displaySetLed(MODE_SEQ, i, C_RED_1);
    }
  }
}

void drawChannelSelect() {
  for(u8 i = 10; i < 50; i++) {
    if(i % 10 >= 1 && i % 10 <= 4) {
      displaySetLed(MODE_SEQ, i, C_YELLOW_1);
      for(u8 step = 0; step < 32; step ++) {
        if(drum[lookupPadToChannel[i]][step] > 0) {
          displaySetLed(MODE_SEQ, i, C_YELLOW_2);
          break;
        }
      }
    }
  }
}

void quantizeCurrentChannel() {
  for(u8 i = 0; i < 32; i++) {
    if(drum[channel][i] > 0) {
      drum[channel][i] = 100;
    }
  }
  drawChannel(channel);
}

void clearCurrentChannel() {
  for(u8 i = 0; i < 32; i++) {
    drum[channel][i] = 0;
  }
  drawChannel(channel);
}

void seqSurfaceEventHandler(u8 type, u8 index, u8 value) {
  if (index > 10 && index < 90 && index % 10 >= 5 && index % 10 <= 8) {
    // set note on pattern
    if(value > 0) {
      if(drum[channel][lookupPadToStep[index]] > 0) {
        drum[channel][lookupPadToStep[index]] = 0;
        displaySetLed(MODE_SEQ, index, C_OFF);
      } else {
        drum[channel][lookupPadToStep[index]] = value;
        displaySetLed(MODE_SEQ, index, (value<<16)+(value<<8)+value);
      }
    }
  } else if (index > 50 && index < 90 && index % 10 >= 1 && index % 10 <= 4) {
    // play note
    if(value > 0) {
      displaySetLed(MODE_SEQ, index, (value<<16));
      midiPlayNoteDirect(lookupPadToMidiNote[index], value);
    } else {
      displaySetLed(MODE_SEQ, index, C_RED_1);
    }
  } else if(index > 10 && index < 50 && index % 10 <=4 && index % 10 >= 1) {
    // set channel
    if(value > 0) {
      channel = lookupPadToChannel[index];
      drawChannelSelect();
      displaySetLed(MODE_SEQ, index, C_GREEN_4);
      drawChannel(channel);
    }
  } else if(index == BUTTON_QUANTIZE && value > 0) {
    quantizeCurrentChannel();
  } else if(index == BUTTON_DELETE && value > 0) {
    clearCurrentChannel();
  }
}

void seqTimerEventHandler() {
  #define TICK_MS 200

  static u8 ms = TICK_MS;

  if (++ms >= TICK_MS)
  {
    ms = 0;

    step = (step + 1) % 32;
    for(u8 i = 0; i < 16; i++) {
      if(drum[i][step] > 0 ) {
        midiPlayNoteDirect(i + midiNoteOffset, drum[i][step]);
        displaySetLed(MODE_SEQ, lookupMidiNoteToPad[i + midiNoteOffset], drum[i][step] << 16);
      } else {
        displaySetLed(MODE_SEQ, lookupMidiNoteToPad[i + midiNoteOffset], C_RED_1);
      }
    }
    drawChannel(channel);
    displaySetLed(MODE_SEQ, lookupStepToPad[step], C_GREEN_4);
  }
}


void seqInit() {
  drawPads();
  drawChannelSelect();
  displaySetLed(MODE_SEQ, 11, C_GREEN_4);
  displaySetLed(MODE_SEQ, BUTTON_DELETE, C_RED_4);
  displaySetLed(MODE_SEQ, BUTTON_QUANTIZE, C_BLUE_4);
}