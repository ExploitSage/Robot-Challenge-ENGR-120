/**
 * Gyro.h
 * Purpose: Control for an L3G4200D 3-axis gyro using SPI
 * 
 * @author <a href="mailto:gus3@michelfamily.org">Gustave A. Michel III</a>
 * @version 1.0 10/30/13
 * @license The GNU Pulic Liscense v3
 */
#ifndef Gyro_h
#define Gyro_h

/*************************
    L3G4200D Registers
*************************/
#define WHO_AM_I 0x0F
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define REFERENCE 0x25
#define OUT_TEMP 0x26
#define STATUS_REG 0x27
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D
#define FIFO_CTRL_REG 0x2E
#define FIFO_SRC_REG 0x2F
#define INT1_CFG 0x30
#define INT1_SRC 0x31
#define INT1_TSH_XH 0x32
#define INT1_TSH_XL 0x33
#define INT1_TSH_YH 0x34
#define INT1_TSH_YL 0x35
#define INT1_TSH_ZH 0x36
#define INT1_TSH_ZL 0x37
#define INT1_DURATION 0x38

#include "Arduino.h"

class Gyro {
  public:
    /**
     * Constructor. Reversed motors can be taken care of by reversing the min/max positions for said motor
     * @param left_pin Arduino pin for left motor
     * @param right_pin Arduino pin for right motor
     * @param left_min Left motor minimum pulse width
     * @param left_stop Left motor stop pulse width
     * @param left_max Left motor maximum pulse width
     * @param right_min Right motor minimum pulse width
     * @param right_stop Right motor stop pulse width
     * @param right_max Right motor maximum pulse width
     * @since v1.0
     */
    Drive(uint8_t left_pin, uint8_t right_pin,
      uint16_t left_min, uint16_t left_stop, uint16_t left_max,
      uint16_t right_min, uint16_t right_stop, uint16_t right_max
    );
    /**
     * Initializes motors after empty constructor. Reversed motors can be taken care of by reversing the min/max positions for said motor
     * @param left_pin Arduino pin for left motor
     * @param right_pin Arduino pin for right motor
     * @param left_min Left motor minimum pulse width
     * @param left_stop Left motor stop pulse width
     * @param left_max Left motor maximum pulse width
     * @param right_min Right motor minimum pulse width
     * @param right_stop Right motor stop pulse width
     * @param right_max Right motor maximum pulse width
     * @since v1.0
     */
    void init(uint8_t left_pin, uint8_t right_pin,
      uint16_t left_min, uint16_t left_stop, uint16_t left_max,
      uint16_t right_min, uint16_t right_stop, uint16_t right_max
    );
  private:
    /**
     * checks if motors should be updated (20ms)
     * @return if 20ms has passed and motors can be updated
     * @since v1.0
     */
    bool is_update_time();
    bool _init; //Retains if Servo objects have been initialized
};

#endif
