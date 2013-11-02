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
    5, 4, //Left, Right, Servo Pins
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
    12, 10, 11, 9 //pins for bits of slector switch
  );
  /*delay(100);
  gyro.init(
    9, 8, 10, S250 //pins and bandwidth for gyro
  );*/
  switch(mode_switch.get_position()) {
    case 0x0:
      //Do Nothing
      break;
    case 0x1:
      nano_chemical();
      break;
    case 0x2:
      electrical_mechanical();
      break;
    case 0x3:
      biomedical();
      break;
    case 0x4:
      civil();
      break;
    case 0x5:
      cyber();
      break;
    case 0x6:
      
      break;
    case 0x7:
      
      break;
    case 0x8:
      
      break;
    case 0x9:
      
      break;
    case 0xA:
      
      break;
    case 0xB:
      
      break;
    case 0xC:
      
      break;
    case 0xD:
      
      break;
    case 0xE:
      
      break;
    case 0xF:
      
      break;
  }
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
  /*
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
  */
  /*gyro.update();
  gyro.update_heading();
  if(gyro.get_heading_z() <80) {
    drive_train.tank_drive(10, -10);
  } else if(gyro.get_heading_z() >80) {
    drive_train.tank_drive(-10, 10);
  }*/
  
  
}

void nano_chemical() {
  forward(90); //Duck Moved
  backward(60);
  left_pivot(45);
  forward(40); //Duck Picked Up
  left_pivot(75);
  forward(70);
}

void electrical_mechanical() {
  forward(35);
  left_spin(15);
  forward(110);
  right_spin(15);
  forward(45);
  right_pivot(20);
  forward(20);
  right_pivot(20);
  forward(60);
  right_pivot(25);
  forward(25); //Duck Placed
  backward(45);
  right_spin(35);
  forward(20); //Duck Pi
  //left_pivot(20);//Duck Picked Up
  forward(50);
  left_pivot(20);
  forward(70);
  left_pivot(30);
  forward(80);
}

void biomedical() {
  forward(35);
  left_spin(15);
  forward(110);
  right_spin(15);
  forward(45);
  right_pivot(20);
  forward(30);
  right_spin(20);
  forward(50); //Duck Placed
  backward(50);
  right_spin(30);
  forward(95);
  left_spin(20);
  forward(180);
}

void civil() {
  forward(50);
  left_pivot(15);
  forward(20);
  backward(20);
  right_pivot(15);
  backward(60);
}

void cyber() {
  
}



void forward(uint16_t loops) {
  for(int i = 0; i < loops; i++) {
    drive_train.tank_drive(100, 100);
    delay(20);
  }
  drive_train.stop();
}

void left_pivot(uint16_t loops) {
  for(int i = 0; i < loops; i++) {
    drive_train.tank_drive(0, 100);
    delay(20);
  }
  drive_train.stop();
}

void right_pivot(uint16_t loops) {
  for(int i = 0; i < loops; i++) {
    drive_train.tank_drive(100, 0);
    delay(20);
  }
  drive_train.stop();
}

void left_spin(uint16_t loops) {
  for(int i = 0; i < loops; i++) {
    drive_train.tank_drive(-100, 100);
    delay(20);
  }
  drive_train.stop();
}

void right_spin(uint16_t loops) {
  for(int i = 0; i < loops; i++) {
    drive_train.tank_drive(100, -100);
    delay(20);
  }
  drive_train.stop();
}

void backward(uint16_t loops) {
  for(int i = 0; i < loops; i++) {
    drive_train.tank_drive(-100, -100);
    delay(20);
  }
  drive_train.stop();
}
