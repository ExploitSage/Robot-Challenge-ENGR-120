/**
 * Drive.h
 * Purpose: Run a Drive Train using a PWM Signal to control a Left and Right Wheel, could work with Servos, or Other Common Motor Controllers (Victors, Jaguars, Talons)
 * 
 * @author <a href="mailto:gus3@michelfamily.org">Gustave A. Michel III</a>
 * @version 1.0 10/26/13
 * @license The GNU Pulic Liscense v3
 */
#ifndef Drive_h
#define Drive_h

#include "Arduino.h"
#include <Servo.h>

#define MIN_SPEED 1300 //Defaults from Parallax
#define STOP_SPEED 1500 //Continous Rotation Servo
#define MAX_SPEED 1700

class Drive {
  public:
    /**
     * Empty constructor, an init() method must be called before instance use
     * @since v1.0
     */
    Drive();
    /**
     * Constructor, defaults pulse positions
     * @param left_pin Arduino pin for left motor
     * @param right_pin Arduino pin for right motor
     * @since v1.0
     */
    Drive(uint8_t left_pin, uint8_t right_pin);
    /**
     * Constructor, defaults stop pulse position. Reversed motors can be taken care of by reversing the min/max positions for said motor
     * @param left_pin Arduino pin for left motor
     * @param right_pin Arduino pin for right motor
     * @param left_min Left motor minimum pulse width
     * @param left_max Left motor maximum pulse width
     * @param right_min Right motor minimum pulse width
     * @param right_max Right motor maximum pulse width
     * @since v1.0
     */
    Drive(uint8_t left_pin, uint8_t right_pin,
          uint16_t left_min, uint16_t left_max,
          uint16_t right_min, uint16_t right_max
    );
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
     * Initializes motors after empty constructor, defaults pulse positions
     * @param left_pin Arduino pin for left motor
     * @param right_pin Arduino pin for right motor
     * @since v1.0
     */
    void init(uint8_t left_pin, uint8_t right_pin);
    /**
     * Initializes motors after empty constructor, defaults stop pulse position. Reversed motors can be taken care of by reversing the min/max positions for said motor
     * @param left_pin Arduino pin for left motor
     * @param right_pin Arduino pin for right motor
     * @param left_min Left motor minimum pulse width
     * @param left_max Left motor maximum pulse width
     * @param right_min Right motor minimum pulse width
     * @param right_max Right motor maximum pulse width
     * @since v1.0
     */
    void init(uint8_t left_pin, uint8_t right_pin,
      uint16_t left_min, uint16_t left_max,
      uint16_t right_min, uint16_t right_max
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
    /**
     * Drives motors by giving speeds for left and right motors individually
     * @param left_speed speed from -100 to 100 for left motor
     * @param right_speed speed from -100 to 100 for right motor
     * @since v1.0
     */
    void tank_drive(uint8_t left_speed, uint8_t right_speed);
    /**
     * Drives motors by giving speeds for left and right motors individually
     * @param left_speed speed in micros pulse width for left motor
     * @param right_speed speed in micros pulse width for right motor
     * @since v1.0
     */
    void tank_drive_micros(uint8_t left_speed, uint8_t right_speed);
    /**
     * @todo add arcade_drive method to use forward/backwards speed and left/right rotation
     */
    //void arcade_drive(uint8_t speed, uint8_t rotate);
    /**
     * sets both motors to stop pulse width
     * @since v1.0
     */
    void stop();
    /**
     * gets speed from left motor
     * @return motor speed from -100 to 100
     * @since v1.0
     */
    uint8_t get_left_speed();
    /**
     * gets speed from left motor
     * @return motor speed in micros
     * @since v1.0
     */
    uint16_t get_left_speed_micros();
    /**
     * gets speed from right motor
     * @return motor speed from -100 to 100
     * @since v1.0
     */
    uint8_t get_right_speed();
    /**
     * gets speed from right motor
     * @return motor speed in micros
     * @since v1.0
     */
    uint16_t get_right_speed_micros();
  private:
    /**
     * checks if motors should be updated (20ms)
     * @return if 20ms has passed and motors can be updated
     * @since v1.0
     */
    bool is_update_time();
    /**
     * restrains input to valid range
     * @param speed input speed
     * @return input restrained to -100 to 100
     * @since v1.0
     */
    uint8_t restrain_limits(uint32_t speed);
    /**
     * restrains input to valid range
     * @param speed input speed
     * @param is_left is the input for left motor or not(right motor)
     * @return input restrained to valid micros pulse widths
     * @since v1.0
     */
    uint16_t restrain_limits_micros(uint32_t pulse_width, bool is_left);
    /**
     * updates motor servo objects
     * @param left_speed left motor speed from -100 to 100 or micros pulse width
     * @param right_speed right motor speed from -100 to 100 or micros pulse width
     * @param is_micros if the speed inputs are pulse widths or not(-100 to 100)
     * @since v1.0
     */
    void set_motors(uint16_t left_speed, uint16_t right_speed, bool is_micros);
    Servo _left_motor; //Left Wheel Servo object
    uint16_t _left_min; //Left Wheel min output (in microsmicros)
    uint16_t _left_stop; //Left Wheel stop output (in micros)
    uint16_t _left_max; //Left WHeel max output (in micros)
    Servo _right_motor; //Right Wheel Servo object
    uint16_t _right_min; //Right Wheel min output (in micros)
    uint16_t _right_stop; //Right Wheel stop output (in micros)
    uint16_t _right_max; //Right Wheel max output (in micros)
    uint32_t last_update; //Records time of last servo update
    bool _init; //Retains if Servo objects have been initialized
};

#endif
