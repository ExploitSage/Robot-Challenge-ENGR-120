/**
 * Mode_Switch.h
 * Purpose: Wrapper for 4-bit Switch input
 * 
 * @author <a href="mailto:gus3@michelfamily.org">Gustave A. Michel III</a>
 * @version 1.0 10/29/13
 * @license The GNU Pulic Liscense v3
 */
#ifndef Mode_Switch_h
#define Mode_Switch_h

#include "Arduino.h"

class Mode_Switch {
  public:
    /**
     * Empty constructor, an init() method must be called before instance use
     * @since v1.0
     */
    Mode_Switch();
    /**
     * Constructor
     * @param bit0 Least Significant bit
     * @param bit1 Second Least Significant bit pin
     * @param bit2 Second Most Significant bit pin
     * @param bit3 Most Significant bit pin
     * @since v1.0
     */
    Mode_Switch(uint8_t bit0, uint8_t bit1, uint8_t bit2, uint8_t bit3);
    /**
     * Initializes Mode Switch
     * @param bit0 Least Significant bit
     * @param bit1 Second Least Significant bit pin
     * @param bit2 Second Most Significant bit pin
     * @param bit3 Most Significant bit pin
     * @since v1.0
     */
    void init(uint8_t bit0, uint8_t bit1, uint8_t bit2, uint8_t bit3);
    /**
     * Returns number collected from input pins
     * @return the value from the switch
     * @since v1.0
     */
    uint8_t get_position();
  private:
    uint8_t _bit0; //Least Significant bit
    uint8_t _bit1; //Second Least Significant bit pin
    uint8_t _bit2; //Second Most Significant bit pin
    uint8_t _bit3; //Most Significant bit pin
    bool _init; //Retains if Object has been initialized
};

#endif
