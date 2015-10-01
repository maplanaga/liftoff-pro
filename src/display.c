#include "display.h"

u8 activeBuffer = MODE_SESSION;

// this takes up 2 KB of the 20 KB of RAM, so idk there might be some optimization potential here
u32 buffers[NUM_MODES][64];

void writeLed(u8 index, u32 color) {
  hal_plot_led(TYPEPAD, index, (color >> 16) & 0xff, (color >> 8) & 0xff, (color >> 0) & 0xff);
}

void displaySetActiveBuffer(u8 buffer) {
  activeBuffer = buffer;
  for (u8 i = 0; i < 64; i++) {
    u32 color = buffers[activeBuffer][i];
    writeLed(lookupIndexToPad[i], color);
  }
  for(u8 i = 95; i <= 98; i++) {
    writeLed(i, C_OFF);
  }
  switch (buffer) {
    case MODE_SESSION : writeLed(95, C_SESSION); break;
    case MODE_PERFORM : writeLed(96, C_PERFORM); break;
    case MODE_SEQ     : writeLed(96, C_SEQ); break;
    case MODE_DEVICE  : writeLed(97, C_DEVICE); break;
    case MODE_USER    : writeLed(98, C_USER); break;
  }
}

void displaySetLed(u8 index, u32 color) {
  writeLed(index, color);
}

void displaySetPad(u8 buffer, u8 index, u32 color) {
  if(index < 64) {
    if(buffer == activeBuffer) {
      writeLed(lookupIndexToPad[index], color);
    }
    buffers[buffer][index] = color;
  }
}

void displaySetButton(u8 index, u32 color) {
  if(index % 10 == 0 || index % 10 == 9 || index < 10 || (index > 90 && index < 95)) {
    writeLed(index, color);
  }
}

void displaySetPadXY(u8 buffer, u8 column, u8 row, u32 color) {
  if(row < 8 && column < 8) {
    u8 index = (8 - row) * 10 + (column + 1);
    if(buffer == activeBuffer) {
      writeLed(index, color);
    }
    buffers[buffer][lookupPadToIndex[index]] = color;
  }
}

void displayClearPads(u8 buffer) {
  for(u8 i = 0; i < 64; i++) {
    if(buffer == activeBuffer) {
      writeLed(lookupIndexToPad[i], C_OFF);
    }
    buffers[buffer][lookupIndexToPad[i]] = C_OFF;
  }
}

u8 randomizer = 0;
u32 displayGetRandomColor() {
  randomizer = (randomizer + 1) % 255;
  return (((randomizer * 10) % 255) << 16) + (((randomizer * randomizer) % 255) << 8) + ((randomizer + 100) % 255);
}