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
* [PhantomYoYo Moisture Sensor](https://www.amazon.com/Arduino-compatible-Sensitivity-Moisture-Sensor/dp/B00AFCNR3U)
* [SMAKN® DHT22 / AM2302 Digital Temp/Humid Sensor](https://www.amazon.com/Digital-Temperature-Humidity-measure-Arduino/dp/B018JO5BRK/ref=sr_1_3?ie=UTF8&qid=1487101256&sr=8-3&keywords=dht22)

## Firmware
The firmware is available at (https://github.com/UWRF-DoTS/soil-moisture-monitor). It is a modified version of the [original Trackuino firmware](https://github.com/trackuino/trackuino) to support the device's purposes. 
