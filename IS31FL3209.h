/**
 * IS31FL3209 LED Driver Library
 * 
 * This is an Arduino library to interface with the Integrated 
 * Silicon Solution, Inc IS31FL3209 18 channel LED Driver.
 * This library handles initializing and controlling the LED
 * Driver.
 * (http://ams.issi.com/WW/pdf/IS31FL3209.pdf)
 * 
 * Author: Rob Rehr (@mediumrehr)
 * Created: Oct 3, 2019
 * 
 * Tested with Arduino 1.8.8
 */

#ifndef IS31FL3209_h
#define IS31FL3209_h

#include <Arduino.h>
#include <Wire.h>

/* registers */
#define REG_SW_SHUTDOWN     0x00
#define REG_PWM             0x01
#define REG_UPDATE          0x13
#define REG_LED_CONTROL     0x14
#define REG_GLOBAL_CONTROL  0x26
#define REG_OUTPUT_FREQ     0x27
#define REG_RESET           0x2F

/* register options */
#define OP_MODE_SHUTDOWN   0x00
#define OP_MODE_NORMAL     0x01

#define PWM_FREQ_23KHZ      0x00
#define PWM_FREQ_3KHZ       0x01

#define GLOBAL_LED_ENABLE   0x00
#define GLOBAL_LED_DISABLE  0x01

/* i2c address options for IS31FL3209 */
#define AD_GND_ADDR         0x6C // AD pin to GND
#define AD_VCC_ADDR         0x6F // AD pin to VCC
#define AD_SCL_ADDR         0x6D // AD pin to SCL
#define AD_SDA_ADDR         0x6E // AD pin to SDA

/* channel count */
#define NUM_CHANNELS        18u

class IS31FL3209 {
  public:
    void begin(TwoWire &wireInst, uint8_t address = AD_GND_ADDR, uint8_t PWMFreq = PWM_FREQ_23KHZ);
    void setOperationMode(bool mode);
    void setChannelPWM(uint8_t channel, uint8_t PWMVal);
    void setAllChannelsPWM(uint8_t PWMVal);
    void setChannelCurrent(uint8_t channel, uint8_t currentVal);
    void setAllChannelsCurrent(uint8_t currentVal);
    void setChannel(uint8_t channel, uint8_t PWMVal, uint8_t currentVal);
    void setAllChannels(uint8_t PWMVal, uint8_t currentVal);
    void updateChannels(void);
    void setGlobalControl(bool mode);
    void setPWMFrequency(bool mode);
    void resetRegisters(void);

  private:
    TwoWire *_wire;
    uint8_t _addr;
    
    void writeByte(uint8_t reg, uint8_t val);
    void writeBytes(uint8_t startingReg, uint8_t numBytes, uint8_t* val);
};

#endif /* IS31FL3209_h */
