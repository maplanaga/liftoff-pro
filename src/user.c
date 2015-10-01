#include "user.h"

void userInit() {

}

void userPadEventHandler(u8 index, u8 value) {
  displaySetPad(MODE_USER, index, C_USER);
}


void userButtonEventHandler(u8 index, bool value) {
  displaySetButton(index, C_USER);
}