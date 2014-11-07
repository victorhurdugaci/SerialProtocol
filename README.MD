Serial Protocol
======

SerialProtocol is a protocol for sending data between two Arduino devices, or between an Arduino and another device through a serial port.

#### Message structure

- Message start marker: 1 byte
- Message size: 1 byte
- Payload (message body): variable number of bytes (max 255)
- Checksum: 1 byte

Total message size (bytes): Payload + 3

#### License

Copyright [Victor Hurdugaci](http://victorhurdugaci.com). All rights reserved.  
Licensed under the Apache License, Version 2.0. See LICENSE in the project root for license information.

#### Acknowledgements

SerialProtocol is inspired by [Arduino-EasyTransfer](https://github.com/madsci1016/Arduino-EasyTransfer). It brings a few improvements (over v2.1):

- The start marker (header) is one byte shorter
- A detailed error code is given in case of communication failures
