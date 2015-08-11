#include "midi.h"

void midiPlayNoteDirect(u8 index, u8 value) {
  hal_send_midi(USBSTANDALONE, NOTEON, index, value);
}