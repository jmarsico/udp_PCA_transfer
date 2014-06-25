udp_PCA_transfer
================

receive UDP string, send i2c to PCA9685. requires wiringPi


# ofxPCA9685
wraps the setup and i2c communication with [NXP's PCA9685 PWM IC](http://www.nxp.com/products/interface_and_connectivity/i2c/i2c_led_display_control/series/PCA9685.html) into a simple and scalable set of functions. 

The PCA9685 chip has 16 12bit PWM channels can be used in circuits to control everything from LEDs to DC motors. 

A breakout board version of the chip is available from [Adafruit](http://www.adafruit.com/product/815)

The addon is based a [Stack Overflow post](http://stackoverflow.com/questions/16025335/undefined-functions-in-class) by user Tom. I think he might have modified some code from Adafruit's Arduino library for this unit.

The addon has only been tested on the RaspberryPi. 

##Dependencies:  
[openFrameworks](http://openframeworks.cc/)

[WiringPi](http://wiringpi.com/)

[ofxWiringPi](https://github.com/joshuajnoble/ofxWiringPi)

