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
 * L3G4200D Registers
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

#define S250 0x80
#define S500 0x90
#define S2000 0xA0
#define S250DPS .00875f
#define S500DPS .0175f
#define S2000DPS .07f
#define GYRO_CS 10

#define  NUM_SAMPLES  50           // As recommended in datasheet
#define  SIGMA_MULTIPLE  3         //

#include "Arduino.h"
#include <SPI.h>

class Gyro {
public:
  /**
   * Constructor, init() function must be called before instance used
   * @since v1.0
   */
  Gyro();
  /**
   * init, Assumes CS, after empty constructor
   * @param int1 
   * @param int2 
   * @since v1.0
   */
  void init(uint8_t int1, uint8_t int2);
  /**
   * init, after empty constructor
   * @param int1 
   * @param int2 
   * @param cs
   * @since v1.0
   */
  void init(uint8_t int1, uint8_t int2, uint8_t cs);
  /**
   * init, after empty constructor
   * @param int1 
   * @param int2 
   * @param cs
   * @param bandwidth
   * @since v1.0
   */
  void init(uint8_t int1, uint8_t int2, uint8_t cs, uint8_t bandwidth);
  
  /**
   * Calibrates centers and thresholds 
   * @since v1.0
   */
  void calibrate();
  /**
   * Updates gyro data values
   */
  void update();
  
  void update_heading();
  /**
   * Gets value from X axis
   * @return value of X axis
   * @since v1.0
   */
  int16_t get_raw_x();
  /**
   * Gets value from Y axis
   * @return value of Y axis
   * @since v1.0
   */
  int16_t get_raw_y();
  /**
   * Gets value from Z axis
   * @return value of Z axis
   * @since v1.0
   */
  int16_t get_raw_z();
  
  int16_t get_dps_x();
  int16_t get_dps_y();
  int16_t get_dps_z();

  float get_heading_x();
  float get_heading_y();
  float get_heading_z();
  /**
   * Checks status Reg for new data
   * @return if new gyro data is avalible
   * @since v1.0
   */
  bool has_new_data();
  /**
   * Checks status Reg for missed data
   * @return if you have missed a dataset from the gyro
   * @since v1.0
   */
  bool has_missed_data();
private:
  /**
   * checks if motors should be updated (20ms)
   * @return if 20ms has passed and motors can be updated
   * @since v1.0
   */
  uint64_t get_deltaT_micros();
  /**
   * Reads Gyro Register
   * @param address the register address
   * @return value from register
   * @since v1.0
   */
  int8_t read_register(uint8_t address);
  /**
   * Writes to Gyro Register
   * @param address the register address
   * @param data data to be written
   * @since v1.0
   */
  void write_register(uint8_t address, int8_t data);
  uint8_t _int1;
  uint8_t _int2;
  uint8_t _cs;
  uint8_t _dps_per_raw; //for Convertion to degrees per second
  int16_t _raw[3];
  int16_t _dps[3];
  float _heading[3];
  int32_t _counter[3];
  int16_t _zero[3]; // Calibration, The center is zero, but the gyro always reports a small amount of rotation.
  int16_t _threshold[3]; // Raw rate change less than this derived threshold is discarded. (formula from datasheet)
  bool _missed_data;
  bool _init; //Retains if Servo objects have been initialized
};

#endif

