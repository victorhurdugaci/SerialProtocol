Arduino Serial Protocol
======

ArduinoSerialProtocol is a protocol for sending data between two Arduino and/or Raspberry PI devices over serial.

#### Message structure

- Message start marker: 1 byte
- Message size: 1 byte
- Payload (message body): variable number of bytes (max 255)
- Checksum: 1 byte

Total message size (bytes): Payload + 3

#### Install Arduino Libraries

1. Download the Repository as a .zip file. 
2. In Arduino IDE, go to Sketch> Include Library> Add .zip Library.
3. Select the Downloaded .zip File.

#### Examples

Arduino Instructions

Open the `arduino_app` in the Arduino IDE and upload to your Arduino.  

Raspberry Pi Instructions

1. Clone this repository and navigate to the `SerialProtocol/extras/raspberry_app` folder. 
2. Make the file `raspberry_app.cpp`
3. Run the new file.  You should see the two devices exchanging a data structure with different numeric types.

#### Acknowledgements

SerialProtocol is inspired by [Arduino-EasyTransfer](https://github.com/madsci1016/Arduino-EasyTransfer). It brings a few improvements (over v2.1):

- The start marker (header) is one byte shorter
- A detailed error code is given in case of communication failures

#### License

Copyright [Victor Hurdugaci](http://victorhurdugaci.com). All rights reserved.  
Licensed under the Apache License, Version 2.0. See LICENSE in the project root for license information.

#### Contributors
[Victor Hurdugaci](http://victorhurdugaci.com)

[James Head](https://github.com/headHUB)
