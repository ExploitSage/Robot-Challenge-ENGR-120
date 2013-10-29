#include "Mode_Switch.h"

Mode_Switch::Mode_Switch() {
  _init = false;
}

Mode_Switch::Mode_Switch(uint8_t bit0, uint8_t bit1, uint8_t bit2, uint8_t bit3) {
  _bit0 = bit0;
  _bit1 = bit1;
  _bit2 = bit2;
  _bit3 = bit3;
  pinMode(_bit0, INPUT_PULLUP);
  pinMode(_bit1, INPUT_PULLUP);
  pinMode(_bit2, INPUT_PULLUP);
  pinMode(_bit3, INPUT_PULLUP);
  _init = true;
}

void Mode_Switch::init(uint8_t bit0, uint8_t bit1, uint8_t bit2, uint8_t bit3) {
  _bit0 = bit0;
  _bit1 = bit1;
  _bit2 = bit2;
  _bit3 = bit3;
  pinMode(_bit0, INPUT_PULLUP);
  pinMode(_bit1, INPUT_PULLUP);
  pinMode(_bit2, INPUT_PULLUP);
  pinMode(_bit3, INPUT_PULLUP);
  _init = true;
}

uint8_t Mode_Switch::get_position() {
  uint8_t value = 0;
  value << digitalRead(_bit3);
  value << digitalRead(_bit2);
  value << digitalRead(_bit1);
  value << digitalRead(_bit0);
  return value;
}
