// Copyright Victor Hurdugaci (http://victorhurdugaci.com). All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE in the project root for license information.

#ifdef ARDUINO

#include <ArduinoSerialProtocol.h>
    
ArduinoSerialProtocol::ArduinoSerialProtocol(HardwareSerial* serial, uint8_t* payload, uint8_t payloadSize)
    :SerialProtocol(payload, payloadSize)
{
    setSerial(serial);
}

void ArduinoSerialProtocol::setSerial(HardwareSerial* serial)
{
    this->serial = serial;
}

bool ArduinoSerialProtocol::serialAvailable()
{
    return serial != NULL;
}

void ArduinoSerialProtocol::sendData(uint8_t data)
{
    serial->write(data);
}

uint8_t ArduinoSerialProtocol::readData()
{
    return serial->read();
}

#endif
