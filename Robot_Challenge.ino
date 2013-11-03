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
 #define LEFT_PIN 1
 #define CENTER_PIN 2
 #define RIGHT_PIN 3
Drive drive_train;
Photo left_photo;
Photo center_photo;
Photo right_photo;
Mode_Switch mode_switch;
//Gyro gyro;

uint8_t battery = 0;
uint8_t indicator = 13;
double threshold = 7.5;

void setup() {
  Serial.begin(9600);
  pinMode(indicator, OUTPUT);
  drive_train.init(
    5, 4, //Left, Right, Servo Pins
    1300, 1500, 1700, //Left Reverse, Stop, Forward pulse widths
    1700, 1500, 1300 //Right Reverse, Stop, Forward pulse widths
  );
  left_photo.init(1, //Analog Pin
    150, 200 //Black(<=), White(>=) thresholds
  );
  center_photo.init(2, //Analog Pin
    150, 200 //Black(<=), White(>=) thresholds
  );
  right_photo.init(3, //Analog Pin
    150, 200 //Black(<=), White(>=) thresholds
  );
  mode_switch.init(
    11, 9, 10, 8 //pins for bits of slector switch
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
  battery_check();
  delay(100);
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
  forward(20); //Duck Picked Up
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
  int last_detect = 0;
  forward(100);
  while(true) {
      /*
      Serial.print("Left: ");
      Serial.println(left_photo.get_value());
      Serial.print("Center: ");
      Serial.println(center_photo.get_value());
      Serial.print("Right: ");
      Serial.println(right_photo.get_value());
      */
    if(center_photo.is_on_black() && (left_photo.is_on_white() || right_photo.is_on_white())) {
      drive_train.tank_drive(30, 30);
    } else {
      if(left_photo.is_on_black() && right_photo.is_on_white()) {
        drive_train.tank_drive(10, 40);
        last_detect = LEFT_PIN;
      } else if(right_photo.is_on_black() && left_photo.is_on_white()) {
        drive_train.tank_drive(40, 10);
        last_detect = RIGHT_PIN;
      } else if(right_photo.is_on_black() && left_photo.is_on_black()) {
        drive_train.stop();
      } else if(right_photo.is_on_white() && left_photo.is_on_white()) {
        while(!(left_photo.is_on_black() || 
           center_photo.is_on_black() ||
           right_photo.is_on_black())) {
          if(last_detect == LEFT_PIN) {
            drive_train.tank_drive(-10, 10);
          } else if(last_detect == RIGHT_PIN){
            drive_train.tank_drive(10, -10);
          } else {
            drive_train.stop();
          }
        }
        /*for(int i = 0; i < 30000; i++) {
          if(left_photo.is_on_black() || 
             center_photo.is_on_black() ||
             right_photo.is_on_black())
            break;
          drive_train.tank_drive(-10, 10);
        }*/
      }
    }
  }
}


void forward() {forward(1);}
void forward(uint16_t loops) {
  for(int i = 0; i < loops; i++) {
    drive_train.tank_drive(100, 100);
    battery_check();
    delay(20);
  }
  drive_train.stop();
}

void left_pivot() {left_pivot(1);}
void left_pivot(uint16_t loops) {
  for(int i = 0; i < loops; i++) {
    drive_train.tank_drive(0, 100);
    battery_check();
    delay(20);
  }
  drive_train.stop();
}

void right_pivot() {right_pivot(1);}
void right_pivot(uint16_t loops) {
  for(int i = 0; i < loops; i++) {
    drive_train.tank_drive(100, 0);
    battery_check();
    delay(20);
  }
  drive_train.stop();
}

void left_spin() {left_spin(1);}
void left_spin(uint16_t loops) {
  for(int i = 0; i < loops; i++) {
    drive_train.tank_drive(-100, 100);
    battery_check();
    delay(20);
  }
  drive_train.stop();
}

void right_spin() {right_spin(1);}
void right_spin(uint16_t loops) {
  for(int i = 0; i < loops; i++) {
    drive_train.tank_drive(100, -100);
    battery_check();
    delay(20);
  }
  drive_train.stop();
}

void backward() {backward(1);}
void backward(uint16_t loops) {
  for(int i = 0; i < loops; i++) {
    drive_train.tank_drive(-100, -100);
    battery_check();
    delay(20);
  }
  drive_train.stop();
}

void battery_check() {
  double voltage = analogRead(battery)*0.004882813*2;
  if(voltage < threshold)
    digitalWrite(indicator, HIGH);
  else
    digitalWrite(indicator, LOW);
}
