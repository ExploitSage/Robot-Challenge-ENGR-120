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
  drive_train.init(
    1, 1, //Left, Right, Servo Pins
    1700, 1500, 1300, //Left Reverse, Stop, Forward pulse widths
    1300, 1500, 1700 //Right Reverse, Stop, Forward pulse widths
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
  drive_train.tank_drive(100, 100);
  delay(20);
}
