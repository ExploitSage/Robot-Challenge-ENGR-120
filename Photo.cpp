#include "Photo.h"

Photo::Photo() {
  _init = false;
  _pin = 0;
  _black_threshold = 0;
  _white_threshold = 0;
}

Photo::Photo(uint8_t pin) {
  Photo(pin, BLACK_THRESHOLD, WHITE_THRESHOLD);
}

Photo::Photo(uint8_t pin, uint16_t black_threshold, uint16_t white_threshold) {
  _pin = pin;
  pinMode(_pin, INPUT); //Is this really needed for analog?
  _black_threshold = black_threshold;
  _white_threshold = white_threshold;
  _init = true;
}

void Photo::init(uint8_t pin) {
  init(pin, BLACK_THRESHOLD, WHITE_THRESHOLD);
}

void Photo::init(uint8_t pin, uint16_t black_threshold, uint16_t white_threshold) {
  _pin = pin;
  pinMode(_pin, INPUT); //Is this really needed for analog?
  _black_threshold = black_threshold;
  _white_threshold = white_threshold;
  _init = true;
}

bool Photo::is_on_black() {
  if(!_init)
    return false;
  uint16_t reading = analogRead(_pin);
  if(reading <= _black_threshold)
    return true;
  return false;
}

bool Photo::is_on_white() {
  if(!_init)
    return false;
  uint16_t reading = analogRead(_pin);
  if(reading >= _white_threshold)
    return true;
  return false;
}
