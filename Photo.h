/**
 * Photo.h
 * Purpose: Wrapper to interface with the Photoresistors on Analog Pins
 * 
 * @author <a href="mailto:gus3@michelfamily.org">Gustave A. Michel III</a>
 * @version 1.0 10/28/13
 * @license The GNU Pulic Liscense v3
 */
#ifndef Photo_h
#define Photo_h

#include "Arduino.h"

#define BLACK_THRESHOLD 312
#define WHITE_THRESHOLD 712

class Photo {
  public:
    /**
     * Empty constructor, an init() method must be called before instance use
     * @since v1.0
     */
    Photo();
    /**
     * Constructor, defaults thresholds
     * @param pin Arduino pin for Photoresistor
     * @since v1.0
     */
    Photo(uint8_t pin);
    /**
     * Constructor
     * @param pin Arduino pin for Photoresistor
     * @param black_threshold Level at which you are over black, this number or lower
     * @param white_threshold Level at which you are over white, this number or higher
     * @since v1.0
     */
    Photo(uint8_t pin, 
      uint16_t black_threshold, uint16_t white_threshold
    );
    /**
     * Initializes Photoresistor with default thresholds
     * @param pin Arduino pin for Photoresistor
     * @since v1.0
     */
    void init(uint8_t pin);
    /**
     * Initializes Photoresistor with default thresholds
     * @param pin Arduino pin for Photoresistor
     * @param black_threshold Level at which you are over black, this number or lower
     * @param white_threshold Level at which you are over white, this number or higher
     * @since v1.0
     */
    void init(uint8_t pin, 
      uint16_t black_threshold, uint16_t white_threshold
    );
    /**
     * Checks if the Photoresistor is currently over black or not (white)
     * @reurn if the Photoresistor is over black or not
     * @since v1.0
     */
    bool is_on_black();
    /**
     * Checks if the Photoresistor is currently over white or not (black)
     * @reurn if the Photoresistor is over white or not
     * @since v1.0
     */
    bool is_on_white();
  private:
    uint8_t _pin; //Analog Arduino Pin for photoresistor
    uint16_t _white_threshold; //Threshold (>=) for white
    uint16_t _black_threshold; //Threshold (<=) for black
    bool _init; //Retains if Object has been initialized
};

#endif
