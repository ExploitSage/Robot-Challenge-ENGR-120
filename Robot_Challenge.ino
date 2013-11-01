#include "Drive.h"
#include <Servo.h> //For Drive Class
#include "Photo.h"
#include "Mode_Switch.h"
#include "Gyro.h"
#include <SPI.h> //For Gyro Class
/******************Pin Map****************
 * A0 PHOTO (Left)
 * A1 PHOTO (Center)
 * A2 PHOTO (Right)
 * A3
 * A4
 * A5
 * 00 SERIAL
 * 01 SERIAL
 * 02
 * 03
 * 04
 * 05
 * 06 SERVO (Right)
 * 07 SERVO (Left)
 * 08 GYRO (int2)
 * 09 GYRO (int1)
 * 10 GYRO (cs)
 * 11 GYRO (SCK)
 * 12 GYRO (MOSI)
 * 13 GYRO (MISO)
 *****************************************/
Drive drive_train;
Photo left_photo;
Photo center_photo;
Photo right_photo;
Mode_Switch mode_switch;
Gyro gyro;

void setup() {
  Serial.begin(9600);
  drive_train.init(
    7, 6, //Left, Right, Servo Pins
    1300, 1500, 1700, //Left Reverse, Stop, Forward pulse widths
    1700, 1500, 1300 //Right Reverse, Stop, Forward pulse widths
  );
  left_photo.init(0, //Analog Pin
    500, 600 //Black(<=), White(>=) thresholds
  );
  center_photo.init(1, //Analog Pin
    500, 600 //Black(<=), White(>=) thresholds
  );
  right_photo.init(2, //Analog Pin
    500, 600 //Black(<=), White(>=) thresholds
  );
  mode_switch.init(
    4, 5, 6, 7 //pins for bits of slector switch
  );
  gyro.init(
    9, 8, 10, S500 //pins and bandwidth for gyro
  );
}

void loop() {
  /*
  Serial.print("Left: ");
  Serial.print(left_photo.get_value());
  Serial.print(" : ");
  if(left_photo.is_on_black()) {
    Serial.println("Black");
  } else if(left_photo.is_on_white()) {
    Serial.println("White");
  } else {
    Serial.println("Gray");
  }
  Serial.print("Center: ");
  Serial.print(center_photo.get_value() );
  Serial.print(" : ");
  if(center_photo.is_on_black()) {
    Serial.println("Black");
  } else if(center_photo.is_on_white()) {
    Serial.println("White");
  } else {
    Serial.println("Gray");
  }
  Serial.print("Right: ");
  Serial.print(right_photo.get_value());
  Serial.print(" : ");
  if(right_photo.is_on_black()) {
    Serial.println("Black");
  } else if(right_photo.is_on_white()) {
    Serial.println("White");
  } else {
    Serial.println("Gray");
  }
  delay(100);
  */
  
  if(center_photo.is_on_black()) {
    if(left_photo.is_on_black() && right_photo.is_on_white()) {
      for(int i = 0; i < 200; i++) {
        drive_train.tank_drive(-15, -10);
      }
    } else if(left_photo.is_on_white() && right_photo.is_on_black()) {
      for(int i = 0; i < 5; i++) {
        drive_train.tank_drive(-10, -15);
      }
    } else {
      drive_train.tank_drive(25, 25);
    }
  } else {
    for(int i = 0; i < 5; i++) {
      drive_train.tank_drive(-10, -15);
      if(center_photo.is_on_black())
        break;
    }
    for(int i = 0; i < 400; i++) {
      drive_train.tank_drive(-15, -10);
      if(center_photo.is_on_black())
        break;
    }
  }
  
}
