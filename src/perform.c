#include "perform.h"

u8 noteMap[64];
u32 displayMap[64];

#define SCALE_MAJOR 0
#define SCALE_MINOR 1
#define SCALE_PENTATONIC_MAJOR 2
#define SCALE_PENTATONIC_MINOR 3
#define SCALE_PENTATONIC_BLUES 4
#define SCALE_DORIAN           5
#define SCALE_LYDIAN         6
#define SCALE_MIXOLYDIAN    7
#define NUM_SCALES          8
#define MAX_SCALE_INTERVALS 7

static const u8 scaleMap[NUM_SCALES][MAX_SCALE_INTERVALS + 1] = {
  {2, 2, 1, 2, 2, 2, 1, 0},
  {2, 1, 2, 2, 1, 3, 1, 0},
  {2, 2, 3, 2, 3, 0, 0, 0},
  {3, 2, 2, 3, 2, 0, 0, 0},
  {3, 2, 1, 1, 3, 2, 0, 0},
  {2, 1, 2, 2, 2, 1, 2, 0},
  {2, 2, 2, 1, 2, 2, 1, 0},
  {2, 2, 1, 2, 2, 1, 2, 0}
};

// theres surely math for this, but i cant think of it right now

static const u8 lookupIso[29][3] = {
  {0, 0, 0},
  {1, 1, 1},
  {2, 2, 2},
  {3, 8, 8},
  {4, 9, 9},
  {5, 10, 10},
  {6, 11, 16},
  {7, 12, 17},
  {13, 18, 18},
  {14, 19, 24},
  {15, 20, 25},
  {21, 26, 26},
  {22, 27, 32},
  {23, 28, 33},
  {29, 34, 34},
  {30, 35, 40},
  {31, 36, 41},
  {37, 42, 42},
  {38, 43, 48},
  {39, 44, 49},
  {45, 50, 50},
  {46, 51, 56},
  {47, 52, 57},
  {53, 58, 58},
  {54, 59, 59},
  {55, 60, 60},
  {61, 61, 61},
  {62, 62, 62},
  {63, 63, 63}
};

static const u32 scaleColor[NUM_SCALES] = {C_BLUE_4, C_BLUE_3, C_YELLOW_4, C_YELLOW_3, C_YELLOW_1, C_CYAN_4, C_MAGENTA_4, C_MAGENTA_3};

void drawScale(u8 type, bool folded, u8 startOctave, u8 rootNote) {
  u8 padCounter = 0;
  noteMap[padCounter] = startOctave * 12 + rootNote;
  displaySetPad(MODE_PERFORM, padCounter, C_RED_4);
  displayMap[padCounter] = C_RED_4;

  while(padCounter < 63) {
    for(u8 scaleStep = 0; scaleStep < MAX_SCALE_INTERVALS; scaleStep++) {
      if(scaleMap[type][scaleStep] == 0) {break;}
      padCounter++;
      noteMap[padCounter] = noteMap[padCounter - 1] + scaleMap[type][scaleStep];
      if(noteMap[padCounter] % 12 != rootNote) {
        displaySetPad(MODE_PERFORM, padCounter, scaleColor[type]);
        displayMap[padCounter] = scaleColor[type];
      } else {
        displaySetPad(MODE_PERFORM, padCounter, C_RED_4);
        displayMap[padCounter] = C_RED_4;
      }
      if(padCounter == 63) { break;}
    }
  }
}


u8 noteList[28];
void setIsoNote(u8 index, u8 note, u32 color) {
  for(u8 i = 0; i < 3; i++) {
    noteMap[lookupIso[index][i]] = note;
    displaySetPad(MODE_PERFORM, lookupIso[index][i], color);
    displayMap[lookupIso[index][i]] = color;
  }
  noteList[index] = note;
}

void drawScaleIso(u8 type, bool folded, u8 startOctave, u8 rootNote) {
  u8 stepCounter = 0;
  setIsoNote(stepCounter, startOctave * 12 + rootNote, C_RED_4);
  while(stepCounter < 28) {
    for(u8 scaleStep = 0; scaleStep < MAX_SCALE_INTERVALS; scaleStep++) {
      if(scaleMap[type][scaleStep] == 0) {break;}
      stepCounter++;
      if((noteList[stepCounter - 1] + scaleMap[type][scaleStep]) % 12 != rootNote) {
        setIsoNote(stepCounter, noteList[stepCounter - 1] + scaleMap[type][scaleStep], scaleColor[type]);
      } else {
        setIsoNote(stepCounter, noteList[stepCounter - 1] + scaleMap[type][scaleStep], C_RED_4);
      }
      if(stepCounter == 28) { break ;}
    }
  }
}

void redrawScale() {
  displayClearPads(MODE_PERFORM);
  if((bool)coreGetCurrent(_ISO)) {
    drawScaleIso(coreGetCurrent(_SCALE_TYPE), coreGetCurrent(_FOLDED), coreGetCurrent(_OCTAVE), coreGetCurrent(_ROOT_NOTE));
  } else {
    drawScale(coreGetCurrent(_SCALE_TYPE), coreGetCurrent(_FOLDED), coreGetCurrent(_OCTAVE), coreGetCurrent(_ROOT_NOTE));
  }
}

void highlightNote(u8 note, u8 value) {
  for(u8 i = 0; i < 64; i++) {
    if(noteMap[i] == note && value > 0) {
      displaySetPad(MODE_PERFORM, i, (value<<16)+(value<<8)+value);
    } else if(noteMap[i] == note) {
      displaySetPad(MODE_PERFORM, i, displayMap[i]);
    }
  }
}

void shiftOctaveDown(){
  if(coreGetCurrent(_OCTAVE) > 0) {
    coreSetCurrent(_OCTAVE, coreGetCurrent(_OCTAVE) - 1);
    redrawScale();
  }
}

void shiftOctaveUp(){
  if(coreGetCurrent(_OCTAVE) < 10) {
    coreSetCurrent(_OCTAVE, coreGetCurrent(_OCTAVE) + 1);
    redrawScale();
  }
}

void shiftRootNoteDown() {
  if(coreGetCurrent(_ROOT_NOTE) == 0) {
    coreSetCurrent(_ROOT_NOTE, 12);
  } else {
    coreSetCurrent(_ROOT_NOTE, coreGetCurrent(_ROOT_NOTE) + 1);
  }
  redrawScale();
}

void shiftRootNoteUp() {
  coreSetCurrent(_ROOT_NOTE, (coreGetCurrent(_ROOT_NOTE) + 1) % 12);
  redrawScale();
}

void toggleNextScale() {
    coreSetCurrent(_SCALE_TYPE, (coreGetCurrent(_SCALE_TYPE) + 1) % NUM_SCALES);
    displaySetButton(BUTTON_SCENE_1, scaleColor[coreGetCurrent(_SCALE_TYPE)]);
    redrawScale();
}

void toggleFixed() {
  coreSetCurrent(_FIXED, !(bool)coreGetCurrent(_FIXED));
  displaySetButton(BUTTON_SCENE_6, (bool)coreGetCurrent(_FIXED) ? C_GREEN_4 : C_GREEN_1);
  redrawScale();
}

void toggleFolded() {
  coreSetCurrent(_FOLDED, !(bool)coreGetCurrent(_FOLDED));
  displaySetButton(BUTTON_SCENE_7, (bool)coreGetCurrent(_FOLDED) ? C_BLUE_4 : C_BLUE_1);
  redrawScale();
}

void toggleIso() {
  coreSetCurrent(_ISO, !(bool)coreGetCurrent(_ISO));
  displaySetButton(BUTTON_SCENE_8, (bool)coreGetCurrent(_ISO) ? C_RED_4 : C_RED_1);
  redrawScale();
}

void performPadEventHandler(u8 index, u8 value) {
  midiPlayNoteDirect(coreGetCurrent(_CHANNEL), noteMap[index], value);
  highlightNote(noteMap[index], value);
}

void performButtonEventHandler(u8 index, bool value) {
  if (value) {
    // change setting
    switch(index) {
      case BUTTON_UP:       shiftOctaveUp(); break;
      case BUTTON_DOWN:     shiftOctaveDown(); break;
      case BUTTON_LEFT:     shiftRootNoteDown(); break;
      case BUTTON_RIGHT:    shiftRootNoteUp(); break;
      case BUTTON_SCENE_1:  toggleNextScale(); break;
      case BUTTON_SCENE_6:  toggleFixed(); break;
      case BUTTON_SCENE_7:  toggleFolded(); break;
      case BUTTON_SCENE_8:  toggleIso(); break;
    }
  }
}

void performAftertouchEventHandler(u8 index, u8 value) {
  midiSendAftertouchDirect(coreGetCurrent(_CHANNEL), noteMap[index], value);
  highlightNote(noteMap[index], value);
}

void performInit() {
  redrawScale();
  displaySetButton(BUTTON_SCENE_1, scaleColor[coreGetCurrent(_SCALE_TYPE)]);
  displaySetButton(BUTTON_SCENE_6, (bool)coreGetCurrent(_FIXED) ? C_GREEN_4 : C_GREEN_1);
  displaySetButton(BUTTON_SCENE_7, (bool)coreGetCurrent(_FOLDED) ? C_BLUE_4 : C_BLUE_1);
  displaySetButton(BUTTON_SCENE_8, (bool)coreGetCurrent(_ISO) ? C_RED_4 : C_RED_1);

  displaySetButton(BUTTON_UP, C_BLUE_4);
  displaySetButton(BUTTON_DOWN, C_BLUE_4);

  displaySetButton(BUTTON_LEFT, C_BLUE_4);
  displaySetButton(BUTTON_RIGHT, C_BLUE_4);
}

void performMidiInEventHandler(u8 status, u8 d1, u8 d2) {
  if(status == NOTEON) {
    highlightNote(d1, d2);
  } else if(status == NOTEOFF) {
    highlightNote(d1, 0);
  }
}