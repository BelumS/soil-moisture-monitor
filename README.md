An open-source Arduino-based device that transmits soil moisture data using the APRS protocol.

This device is intended for use by licensed Radio amateurs.

## Features
* Send AX.25 APRS packets
* Measure soil moisture content
* Transmit data with 1200 bauds AFSK using 8-bit PWM
* Track the data from an [online portal](https://aprs.fi/#!lat=44.83710&lng=-92.59170)

## Hardware
The device was built using: 
* [Arduino UNO](https://www.arduino.cc/en/Main/ArduinoBoardUno) - a similar microcontroller will also work.
* [Radiometrix HX1 RF Transmitter](http://www.radiometrix.com/content/hx1)
* [DFRobot Gravity: Analog Capacitive Soil Moisture Sensor](https://www.amazon.com/gp/product/B01GHY0N4K/ref=ox_sc_act_title_1?ie=UTF8&psc=1&smid=A2EH5PO307BR7O)

## Firmware
The firmware is available at (https://github.com/UWRF-DoTS/soil-moisture-monitor). It is a modified version of the [original Trackuino firmware](https://github.com/trackuino/trackuino), along with [Project Horus](https://code.google.com/archive/p/project-horus/source/default/source), a fork of the trackuino firmware, to support the device's purposes. 

## Testing
In order to test the device before production release, I had to use the following hardware and software, along with the above firmware.
 * [Baofeng UV-5R+ HAM Radio](https://www.amazon.com/BaoFeng-UV-5R-Dual-Radio-Black/dp/B007H4VT7A)
 * [BTECH APRS-K2 Cable for Baofeng](https://www.amazon.com/APRS-K2-Connector-BaoFeng-APRSDroid-Compatible/dp/B01LMIBAZW)
 * [APRSDroid](https://aprsdroid.org/)
