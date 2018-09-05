// Copyright Victor Hurdugaci (http://victorhurdugaci.com). All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE in the project root for license information.

#ifndef ARDUINO

#include <StreamSerialProtocol.h>

StreamSerialProtocol::StreamSerialProtocol(int serial, uint8_t* payload, uint8_t payloadSize)
    :SerialProtocol(payload, payloadSize)
{
    setSerial(serial);
}

void StreamSerialProtocol::setSerial(int serial)
{
    this->serial = serial;
}

bool StreamSerialProtocol::serialAvailable()
{
    return serial != -1;
}

void StreamSerialProtocol::sendData(uint8_t data)
{
    write(serial, &data, 1);
}

uint8_t StreamSerialProtocol::readData()
{
    uint8_t data[1];
    int cnt = read(serial, (void*)data, 1);
    if (cnt == 0)
    {
        return -1;
    }
    
    return data[0];
}

#endif
