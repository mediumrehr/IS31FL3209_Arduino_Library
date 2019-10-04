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
 
 #include "IS31FL3209.h"

/**
 * begin configures and starts LED driver
 *   @param wireInst twoWire instance to use for sending data to LED driver
 *   @param address 7-bit i2c address of the LED driver
 *   @param PWMFreq setting for PWM output frequency
 *     0x00 - software shutdown mode
 *     0x01 - normal mode
 */
void IS31FL3209::begin(TwoWire &wireInst, uint8_t address = AD_GND_ADDR, uint8_t PWMFreq = PWM_FREQ_23KHZ) {
  _wire = &wireInst;
  _addr = address;

  resetRegisters(); // optional (but register values are held as long as powered)
  setOperationMode(OP_MODE_NORMAL);
  setPWMFrequency(PWMFreq);
  setGlobalControl(GLOBAL_LED_ENABLE); // optional (enabled by default)
}

/**
 * setOperationMode sets the operation mode of the LED driver
 *   @param mode selection for operating mode
 *     0x00 - software shutdown mode
 *     0x01 - normal mode
 */
void IS31FL3209::setOperationMode(bool mode) {
  uint8_t opVal = 0x00 | mode;
  writeByte(REG_SW_SHUTDOWN, opVal);
}

/**
 * setChannelPWM sets PWM duty cycle for a single channel
 *   @param channel channel number to control
 *   @param PWMVal new duty cycle for channel
 *   
 *   @note call updateChannels for change to take effect
 */
void IS31FL3209::setChannelPWM(uint8_t channel, uint8_t PWMVal) {
  writeByte(REG_PWM + (channel - 1), PWMVal);
}

/**
 * setAllChannelsPWM sets PWM duty cycle for all channels
 *   @param PWMVal new duty cycle for all channels
 *   
 *   @note call updateChannels for change to take effect
 */
void IS31FL3209::setAllChannelsPWM(uint8_t PWMVal) {
  // set PWM values
  uint8_t PWMVals[NUM_CHANNELS];
  for (uint8_t i=0; i<NUM_CHANNELS; i++) { PWMVals[i] = PWMVal; }
  writeBytes(REG_PWM, NUM_CHANNELS, PWMVals);
}

/**
 * UpdateChannels pushes changes to the PWM and current registers
 * - it is necessary to call for changes to take effect
 * 
 *    @note call updateChannels for change to take effect
 */
void IS31FL3209::updateChannels(void) {
  writeByte(REG_UPDATE, 0x00);
}

/**
 * setChannelCurrent sets max current for a single channel
 *   @param channel channel number to control
 *   @param currentVal new max current for channel
 *    From datasheet, current value can be the folowing:
 *    0x30 Imax          0x33 19/24 Imax    0x11 11/24 Imax
 *    0x31 23/24 Imax    0x3a 18/24 Imax    0x12  9/24 Imax
 *    0x35 22/24 Imax    0x3e 16/24 Imax    0x13  7/24 Imax
 *    0x32 21/24 Imax    0x3f 14/24 Imax    0x00  0/24 Imax
 *    0x36 20/24 Imax    0x10 12/24 Imax
 *    
 *    @note call updateChannels for change to take effect
 */
void IS31FL3209::setChannelCurrent(uint8_t channel, uint8_t currentVal) {
  writeByte(REG_LED_CONTROL + (channel - 1), currentVal);
}

/**
 * setAllChannelsCurrent sets max current for all channels
 *   @param currentVal new max current for all channels
 *   
 *   @note call updateChannels for change to take effect
 */
void IS31FL3209::setAllChannelsCurrent(uint8_t currentVal) {
  // set current values
  uint8_t currentVals[NUM_CHANNELS];
  for (uint8_t i=0; i<NUM_CHANNELS; i++) { currentVals[i] = currentVal; }
  writeBytes(REG_LED_CONTROL, NUM_CHANNELS, currentVals);
}

/**
 * setChannel sets PWM duty cycle and max current for a single channel
 *   @param channel channel number to control
 *   @param PWMVal new duty cycle for channel
 *   @param currentVal new max current for channel
 *   
 *   @note call updateChannels for change to take effect
 */
void IS31FL3209::setChannel(uint8_t channel, uint8_t PWMVal, uint8_t currentVal) {
  // set PWM value
  writeBytes(REG_PWM, NUM_CHANNELS, PWMVal);
  
  // set current value
  writeBytes(REG_LED_CONTROL, NUM_CHANNELS, currentVal);
}

/**
 * setAllChannels sets PWM duty cycle and max current for all channels
 *   @param PWMVal new duty cycle for all channels
 *   @param currentVal new max current for all channels
 *   
 *   @note call updateChannels for change to take effect
 */
void IS31FL3209::setAllChannels(uint8_t PWMVal, uint8_t currentVal) {
  // set PWM values
  uint8_t PWMVals[NUM_CHANNELS];
  for (uint8_t i=0; i<NUM_CHANNELS; i++) { PWMVals[i] = PWMVal; }
  writeBytes(REG_PWM, NUM_CHANNELS, PWMVals);

  // set current values
  uint8_t currentVals[NUM_CHANNELS];
  for (uint8_t i=0; i<NUM_CHANNELS; i++) { currentVals[i] = currentVal; }
  writeBytes(REG_LED_CONTROL, NUM_CHANNELS, currentVals);
}

/**
 * setGlobalControl sets the global control register for the LED driver
 *   @param mode selection for global control register
 *     0x00 - normal operation
 *     0x01 - shutdown all LEDs
 */
void IS31FL3209::setGlobalControl(bool mode) {
  uint8_t GCVal = 0x00 | mode;
  writeByte(REG_GLOBAL_CONTROL, GCVal);
}

/**
 * setPWMFrequency sets the frequency for the PWM output
 *   @param mdoe selection for the PWM output frequency
 *     0x00 - output freq: 23kHz
 *     0x01 - output freq: 3.45kHz
 */
void IS31FL3209::setPWMFrequency(bool setting) {
  uint8_t PWMVal = 0x00 | setting;
  writeByte(REG_OUTPUT_FREQ, PWMVal);
}

/**
 * resetRegisters resets the LED driver's registers to default
 * values (all zeros)
 */
void IS31FL3209::resetRegisters(void) {
  writeByte(REG_RESET, 0x00);
}

/**
 * writeByte writes a single byte to the LED driver
 *   @param reg register to write to
 *   @param val byte value to write to register
 */
void IS31FL3209::writeByte(uint8_t reg, uint8_t val) {
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  _wire->write(val);
  _wire->endTransmission();
}

/**
 * writeBytes writes multiple bytes to the LED driver
 * bytes are written to registers consecutively
 *   @param reg starting register to write to
 *   @param numBytes number of bytes to write/size of val array
 *   @param val array of bytes to write
 */
void IS31FL3209::writeBytes(uint8_t startingReg, uint8_t numBytes, uint8_t* val) {
  _wire->beginTransmission(_addr);
  _wire->write(startingReg);
  for (uint8_t i=0; i<numBytes; i++) {
    _wire->write(val[i]);
  }
  _wire->endTransmission();
}
