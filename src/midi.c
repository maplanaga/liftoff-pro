#include "midi.h"

bool dinMidiConnected = true;

void midiPlayNoteDirect(u8 channel, u8 index, u8 value) {
  switch(channel) {
    case 0: hal_send_midi(USBSTANDALONE, NOTEON, index, value); break;
    case 1: hal_send_midi(USBMIDI, NOTEON, index, value); break;
    case 2: hal_send_midi(USBMIDI, NOTEON, index, value); break;
    case 3: hal_send_midi(DINMIDI, NOTEON, index, value); break;
  }
}

void midiSendAftertouchDirect(u8 channel, u8 index, u8 value) {
  switch(channel) {
    case 0: hal_send_midi(USBSTANDALONE, POLYAFTERTOUCH, index, value); break;
    case 1: hal_send_midi(USBMIDI, POLYAFTERTOUCH, index, value); break;
    case 2: hal_send_midi(USBMIDI, POLYAFTERTOUCH, index, value); break;
    case 3: hal_send_midi(DINMIDI, POLYAFTERTOUCH, index, value); break;
  }
}