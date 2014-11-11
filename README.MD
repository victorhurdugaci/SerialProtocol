Serial Protocol
======

SerialProtocol is a protocol for sending data between two Arduino and/or Raspberry PI devices over serial.

#### Message structure

- Message start marker: 1 byte
- Message size: 1 byte
- Payload (message body): variable number of bytes (max 255)
- Checksum: 1 byte

Total message size (bytes): Payload + 3

#### Install Arduino Libraries

Copy the `src\SerialProtocol` folder to:

- Windows: `%USERPROFILE%\Victor\Documents\Arduino`
- Linux: `~/sketchbook/libraries` or `/usr/share/arduino/libraries`
- Mac: `Documents/Arduino/libraries`

Note: You must restart the Arduino IDE if it was running before you copied the files.

#### Samples

The `samples` folder contains examples for both Arduino and Raspberry PI. If you upload the Arduino sketch and then run the Raspberry PI application, you should see the two devices exchanging a data structure with different numeric types.

#### Acknowledgements

SerialProtocol is inspired by [Arduino-EasyTransfer](https://github.com/madsci1016/Arduino-EasyTransfer). It brings a few improvements (over v2.1):

- The start marker (header) is one byte shorter
- A detailed error code is given in case of communication failures

#### License

Copyright [Victor Hurdugaci](http://victorhurdugaci.com). All rights reserved.  
Licensed under the Apache License, Version 2.0. See LICENSE in the project root for license information.