/**
 * Example code to show use of the IS31FL3209 LED Driver Library
 * 
 * Author: Rob Rehr (@mediumrehr)
 * Created: Oct 3, 2019
 * 
 * Tested with Arduino 1.8.8
 */
 
#include "IS31FL3209.h"

IS31FL3209 LEDDriver = IS31FL3209();

// number of LEDs on board
// (using channels 1-8)
uint8_t numLEDs = 8;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Wire.setClock(400000);

  // begin the LED Driver controller by sending an
  // instance of Wire (after it's initialized)
  LEDDriver.begin(Wire);
  // set all PWM to 0 (off) and current to 7/24 Imax
  LEDDriver.setAllChannels(0x00, 0x13);
  LEDDriver.updateChannels();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  for (uint8_t i=0; i<numLEDs; i++) {
    // clear staging PWM values
    LEDDriver.setAllChannelsPWM(0x00);
    // set channel i PWM to be turned on
    // (with duty cycle relative to channel number)
    LEDDriver.setChannelPWM(i+1, 1<<i);
    // push new PWM values to register
    LEDDriver.updateChannels();
  
    delay(500);
  }
}
