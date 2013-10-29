#include "Drive.h"
#include <Servo.h> //For Drive Class
#include "Photo.h"
#include "Mode_Switch.h"

Drive drive_train;
Photo left_photo;
Photo center_photo;
Photo right_photo;
Mode_Switch mode_switch;

void setup() {
  Serial.begin(9600);
  drive_train.init(
    11, 10, //Left, Right, Servo Pins
    1300, 1500, 1700, //Left Reverse, Stop, Forward pulse widths
    1700, 1500, 1300 //Right Reverse, Stop, Forward pulse widths
  );
  left_photo.init(0, //Analog Pin
    300, 500 //Black(<=), White(>=) thresholds
  );
  center_photo.init(1, //Analog Pin
    300, 500 //Black(<=), White(>=) thresholds
  );
  right_photo.init(2, //Analog Pin
    300, 500 //Black(<=), White(>=) thresholds
  );
  mode_switch.init(
    4,5,6,7 //bit of slector switch
  );
}

void loop() {
  /*if(center_photo.is_on_black()) {
    if(left_photo.is_on_black() && right_photo.is_on_white()) {
      for(int i = 0; i < 200; i++) {
        drive_train.tank_drive(-30, -20);
      }
    } else if(left_photo.is_on_white() && right_photo.is_on_black()) {
      for(int i = 0; i < 200; i++) {
        drive_train.tank_drive(-20, -30);
      }
    } else {
      drive_train.tank_drive(50, 50);
    }
  } else {
    for(int i = 0; i < 200; i++) {
      drive_train.tank_drive(-20, -30);
      if(center_photo.is_on_black())
        break;
    }
    for(int i = 0; i < 400; i++) {
      drive_train.tank_drive(-30, -20);
      if(center_photo.is_on_black())
        break;
    }
  }*/
  drive_train.tank_drive(-100,-100);
}
