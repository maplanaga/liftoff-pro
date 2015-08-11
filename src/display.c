#include "display.h"

u8 activeBuffer = MODE_SESSION;

// this takes up 2 KB of the 20 KB of RAM, so idk there might be some optimization potential here
u32 buffers[NUM_MODES][NUM_BUTTONS];

void displaySetActiveBuffer(u8 buffer) {
  activeBuffer = buffer;
  for (u8 i = 0; i < 95; i++) {
    u32 color = buffers[activeBuffer][i];
    hal_plot_led(TYPEPAD, i, (color >> 16) & 0xff, (color >> 8) & 0xff, (color >> 0) & 0xff);
  }
  for(u8 i = 95; i <= 98; i++) {
    hal_plot_led(TYPEPAD, i, 0, 0, 0);
  }
  switch (buffer) {
    case MODE_SESSION : writeLed(95, C_SESSION); break;
    case MODE_PERFORM : writeLed(96, C_PERFORM); break;
    case MODE_SEQ     : writeLed(96, C_SEQ); break;
    case MODE_DEVICE  : writeLed(97, C_DEVICE); break;
    case MODE_USER    : writeLed(98, C_USER); break;
  }
}

void displaySetLed(u8 buffer, u8 index, u32 color) {
  if(buffer == activeBuffer && index < 95) {
    writeLed(index, color);
  }
  buffers[buffer][index] = color;
}

void writeLed(u8 index, u32 color) {
  hal_plot_led(TYPEPAD, index, (color >> 16) & 0xff, (color >> 8) & 0xff, (color >> 0) & 0xff);
}