#include "core.h"

u8 selectedChannel = 0;
u8 selectedClip = 0;

u8 coreGetCurrent(u8 type) {
  switch (type) {
    case _CHANNEL     : return selectedChannel;
    case _CLIP        : return selectedClip;
    case _SCALE_TYPE  : return coreChannels[selectedChannel].clips[selectedClip].scaleType;
    case _OCTAVE      : return coreChannels[selectedChannel].clips[selectedClip].octave;
    case _ROOT_NOTE   : return coreChannels[selectedChannel].clips[selectedClip].rootNote;
    case _FOLDED      : return coreChannels[selectedChannel].clips[selectedClip].folded;
    case _FIXED       : return coreChannels[selectedChannel].clips[selectedClip].fixed;
    case _ISO         : return coreChannels[selectedChannel].clips[selectedClip].iso;
    default           : return 0;
  }
}

void coreSetCurrent(u8 type, u8 value) {
  switch (type) {
    case _CHANNEL     : selectedChannel = value; break;
    case _CLIP        : selectedClip = value; break;
    case _SCALE_TYPE  : coreChannels[selectedChannel].clips[selectedClip].scaleType = value; break;
    case _OCTAVE      : coreChannels[selectedChannel].clips[selectedClip].octave = value; break;
    case _ROOT_NOTE   : coreChannels[selectedChannel].clips[selectedClip].rootNote = value; break;
    case _FOLDED      : coreChannels[selectedChannel].clips[selectedClip].folded = value; break;
    case _FIXED       : coreChannels[selectedChannel].clips[selectedClip].fixed = value; break;
    case _ISO         : coreChannels[selectedChannel].clips[selectedClip].iso = value; break;
  }
}

void coreInit() {
    for(u8 i = 0; i < NUM_CHANNELS; i++) {
        coreChannels[i].color = displayGetRandomColor();
    }
}

void playStep() {
    for(u8 i = 0; i < NUM_CHANNELS; i++){
        for(u8 poly = 0; poly < NUM_POLYPHONY; poly++) {
            u8 note = coreChannels[i].clips[coreChannels[i].playing].steps[coreChannels[i].atStep][poly];
            if(note != 0) {
                midiPlayNoteDirect(i, note, 127);
            }
        }
        coreChannels[i].atStep = (coreChannels[i].atStep + 1) % coreChannels[i].clips[coreChannels[i].playing].length;
    }
}

void coreTimerEventHandler() {
    #define TICK_MS 20
    #define PPQN    24

    static u8 ms = TICK_MS;
    static u8 pulse = PPQN;

    if (++ms >= TICK_MS)
    {
        ms = 0;
        if(++pulse >= PPQN) {
            pulse = 0;
            playStep();
            displaySetButton(BUTTON_CLICK, C_YELLOW_4);
        }

        if(pulse == 2) {
            displaySetButton(BUTTON_CLICK, C_YELLOW_1);
        }

        // send a clock pulse up the USB
        // hal_send_midi(USBSTANDALONE, MIDITIMINGCLOCK, 0, 0);
    }
}