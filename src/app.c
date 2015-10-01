/******************************************************************************

 Copyright (c) 2015, Focusrite Audio Engineering Ltd.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 * Neither the name of Focusrite Audio Engineering Ltd., nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 *****************************************************************************/

//______________________________________________________________________________
//
// Headers
//______________________________________________________________________________

#include "app.h"

//______________________________________________________________________________
//
// This is where the fun is!  Add your code to the callbacks below to define how
// your app behaves.
//______________________________________________________________________________

void app_surface_event(u8 type, u8 index, u8 value)
{
	switch (type)
	{
		case TYPEPAD:
		{
  		if(index > 10 && index < 90 && index % 10 >= 1 && index % 10 <= 8){
    		app_pad_event(index, value);
  		} else {
    		app_button_event(index, value);
  		}
		}
		break;

		case TYPESETUP:
		{
			app_setup_event(value);
		}
		break;
	}
}

void app_pad_event(u8 index, u8 value) {
  switch(modeGetCurrent()) {
    case MODE_SESSION : sessionPadEventHandler(lookupPadToIndex[index], value); break;
    case MODE_PERFORM : performPadEventHandler(lookupPadToIndex[index], value); break;
    case MODE_SEQ     : seqPadEventHandler(lookupPadToIndex[index], value);     break;
    case MODE_DEVICE  : devicePadEventHandler(lookupPadToIndex[index], value);  break;
    case MODE_USER    : userPadEventHandler(lookupPadToIndex[index], value);    break;
    case MODE_OVERLAY : overlayPadEventHandler(lookupPadToIndex[index], value); break;
  }
}

void app_button_event(u8 index, bool value) {
  if(index >= 95 && index <=98) {
    modeButtonEventHandler(index, value);
  } else if (index < 10) {
    modeOverlayEventHandler(index, value);
  } else {
    switch(modeGetCurrent()) {
      case MODE_SESSION : sessionButtonEventHandler(index, value); break;
      case MODE_PERFORM : performButtonEventHandler(index, value); break;
      case MODE_SEQ     : seqButtonEventHandler(index,     value); break;
      case MODE_DEVICE  : deviceButtonEventHandler(index,  value); break;
      case MODE_USER    : userButtonEventHandler(index,    value); break;
    }
  }
}

void app_setup_event(bool value) {

}

//______________________________________________________________________________

void app_midi_event(u8 port, u8 status, u8 d1, u8 d2)
{

  performMidiInEventHandler(status, d1, d2);
	// example - MIDI interface functionality for USB "MIDI" port -> DIN port
	//if (port == USBMIDI)
	//{
	//	hal_send_midi(DINMIDI, status, d1, d2);
	//}

	// // example -MIDI interface functionality for DIN -> USB "MIDI" port port
	//if (port == DINMIDI)
	//{
	//	hal_send_midi(USBMIDI, status, d1, d2);
	//}
}

//______________________________________________________________________________

void app_sysex_event(u8 port, u8 * data, u16 count)
{
	// example - respond to UDI messages?
}

//______________________________________________________________________________

void app_aftertouch_event(u8 index, u8 value)
{
  performAftertouchEventHandler(lookupPadToIndex[index], value);
    // example - send poly aftertouch to MIDI ports
	//hal_send_midi(USBMIDI, POLYAFTERTOUCH | 0, index, value);

    // example - set LED to white, brightness in proportion to pressure
	//hal_plot_led(TYPEPAD, index, 0, value/2, value/2);
}

//______________________________________________________________________________

void app_cable_event(u8 type, u8 value)
{
    // example - light the Setup LED to indicate cable connections
	//if (type == MIDI_IN_CABLE)
	//{
	//	hal_plot_led(TYPESETUP, 0, 0, value, 0); // green
	//}
	//else if (type == MIDI_OUT_CABLE)
	//{
	//	hal_plot_led(TYPESETUP, 0, value, 0, 0); // red
	//}
}

//______________________________________________________________________________


void app_timer_event()
{
	coreTimerEventHandler();
}

//______________________________________________________________________________

void app_init()
{
  displaySetActiveBuffer(MODE_SESSION);
  coreInit();
	sessionInit();
	performInit();
	seqInit();
	deviceInit();
	userInit();
	overlayInit();
}

void app_clipchange_event() {
  performInit();
}
