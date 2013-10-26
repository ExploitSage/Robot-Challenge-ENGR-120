#include "Drive.h"

Drive::Drive() { 
  _init = false;
  _left_min = 0;
  _left_stop = 0;
  _left_max = 0;
  _right_min = 0;
  _right_stop = 0;
  _right_max = 0;
}

Drive::Drive(uint8_t left_pin, uint8_t right_pin) {
  Drive(left_pin, right_pin, MIN_SPEED, MAX_SPEED, MIN_SPEED, MAX_SPEED);
}

Drive::Drive(uint8_t left_pin, uint8_t right_pin, uint16_t left_min, uint16_t left_max, uint16_t right_min, uint16_t right_max) {
  Drive(left_pin, right_pin, left_min, STOP_SPEED, left_max, right_min, STOP_SPEED, right_max);
}

Drive::Drive(uint8_t left_pin, uint8_t right_pin, uint16_t left_min, uint16_t left_stop, uint16_t left_max, uint16_t right_min, uint16_t right_stop, uint16_t right_max) {
  _left_min = left_min;
  _left_stop = left_stop;
  _left_max = left_max;
  _left_motor.attach(left_pin, _left_min, _left_max);
  _left_motor.writeMicroseconds(_right_stop);
  _right_min = right_min;
  _right_stop = right_stop;
  _right_max = right_max;
  _right_motor.attach(right_pin, _right_min, right_max);
  _right_motor.writeMicroseconds(_right_stop);
  
  _init = true;
}

void Drive::init(uint8_t left_pin, uint8_t right_pin) {
  init(left_pin, right_pin, MIN_SPEED, STOP_SPEED, MAX_SPEED, MIN_SPEED, STOP_SPEED, MAX_SPEED);
}

void Drive::init(uint8_t left_pin, uint8_t right_pin, uint16_t left_min, uint16_t left_max, uint16_t right_min, uint16_t right_max) {
  init(left_pin, right_pin, left_min, STOP_SPEED, left_max, right_min, STOP_SPEED, right_max);
}

void Drive::init(uint8_t left_pin, uint8_t right_pin, uint16_t left_min, uint16_t left_stop, uint16_t left_max, uint16_t right_min, uint16_t right_stop, uint16_t right_max) {
  _left_min = left_min;
  _left_stop = left_stop;
  _left_max = left_max;
  _left_motor.attach(left_pin, _left_min, _left_max);
  _left_motor.writeMicroseconds(_left_stop);
  _right_min = right_min;
  _right_stop = right_stop;
  _right_max = right_max;
  _right_motor.attach(right_pin, _right_min, right_max);
  _right_motor.writeMicroseconds(_right_stop);
  
  _init = true;
}

void Drive::tank_drive(uint8_t left_speed, uint8_t right_speed) {
  if(!_init || !is_update_time()) //exits method if instance has not been initialized or the motors can't be set yet
    return;
    
  left_speed = restrain_limits(left_speed);
  right_speed = restrain_limits(right_speed);
  
  set_motors(left_speed, right_speed, false); //inputs are not in microseconds
}

void Drive::tank_drive_micros(uint8_t left_speed, uint8_t right_speed) {
  if(!_init || !is_update_time()) //exits method if instance has not been initialized or the motors can't be set yet
    return;
    
  left_speed = restrain_limits_micros(left_speed, true);
  right_speed = restrain_limits_micros(right_speed, false);
  
  set_motors(left_speed, right_speed, true); //inputs are in microseconds
}

void Drive::stop() {
  set_motors(_left_stop, _right_stop, true); //inputs are in microseconds
}

uint8_t Drive::get_left_speed() {
 return map(_left_motor.read(), _left_min, _left_max, -100, 100);
}

uint16_t Drive::get_left_speed_micros() {
  return _left_motor.read();
}

uint8_t Drive::get_right_speed() {
  return map(_right_motor.read(), _right_min, _right_max, -100, 100);
}

uint16_t Drive::get_right_speed_micros() {
  return _right_motor.read();
}

bool Drive::is_update_time() {
  uint32_t current_time = millis();
  if(current_time - last_update >= 20) { //update only every 20ms
    last_update = current_time;
    return true;
  }
  return false;
}

uint8_t Drive::restrain_limits(uint32_t speed) {
  if(speed > 100)
    speed = 100;
  else if(speed < -100)
    speed = -100;
  
  return speed;
}

uint16_t Drive::restrain_limits_micros(uint32_t speed, bool is_left) {
  if(is_left) {
    if(speed > _left_max)
      speed = _left_max;
    else if(speed < _left_min)
      speed = _left_min;
  } else {
    if(speed > _right_max)
      speed = _right_max;
    else if(speed < _right_min)
      speed = _right_min;
  }
  return speed;
}

void Drive::set_motors(uint16_t left_speed, uint16_t right_speed, bool is_micros) {
  if(!is_micros) {
    left_speed = map(left_speed, -100, 100, _left_min, _left_max); //-100 to 100 are valid abstract speed range
    right_speed = map(right_speed, -100, 100, _right_min, _right_max);
  }
  _left_motor.writeMicroseconds(left_speed);
  _right_motor.writeMicroseconds(right_speed);
}
