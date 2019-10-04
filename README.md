## IS31FL3209 Arduino Library

An Arduino library for interfacing with the [ISSI IS31FL3209 LED Driver](http://ams.issi.com/WW/pdf/IS31FL3209.pdf)

Tested on Arduino IDE 1.8.8

### Installation

Download and unzip _or_ clone the repository to the `libraries` directory within your Arduino sketchbook directory (to find the location of this directory, open the Arduino IDE, go to preferences, and the location should be at the top of the Settings tab). Restart the Arduino IDE for the library to be accessible.

### Usage

To use the library, first include it in your sketch by adding `#include "IS31FL3209.h"` to the top. Next, create an instance of the driver class by calling `IS31FL3209 LEDDriver = IS31FL3209()`. You must call `LEDDriver.begin(Wire)` (where `Wire` is an [Arduino Wire](https://www.arduino.cc/en/reference/wire) instance you've already initialized) before you will be able to control any of the channels since the LED Driver is disabled by default.

Common commands are:
```
setAllChannels - set both PWM duty cycle and max current for all driver channels
setChannel - set both PWM duty cycle and max current for a single driver channel
setAllChannelsCurrent - set the max current for all driver channels
setChannelCurrent - set the max current for a single driver channel
setAllChannelsPWM - set the PWM duty cycle for all driver channels
setChannelPWM - set the PWM duty cycle for a single driver channel
```

As stated in the IS31FL3209 datasheet, set changes to PWM and current registers are only staged, and aren't pushed to the registers until `updateChannels()` is called.

Please check the example sketch and library files for better explanation and documentation of use.

### License

MIT Lincense

You are free to use, copy, modify, etc, just know that this is provided 'as is' and without warranty. See the `License` file for more information.

Additionally, if you find this library helpful and/or use it in a project, I'd love to know!
