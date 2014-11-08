// Copyright Victor Hurdugaci (http://victorhurdugaci.com). All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE in the project root for license information.

#ifndef ARDUINO
#ifndef STREAMSERIALPROTOCOL_H
#define STREAMSERIALPROTOCOL_H

#include <stdint.h>
#include <unistd.h>
#include <SerialProtocol.h>

class StreamSerialProtocol : public SerialProtocol 
{
public:
    StreamSerialProtocol(int, uint8_t*, uint8_t);

    void setSerial(int);
    
protected:
    bool serialAvailable();

    void sendData(uint8_t data);
    uint8_t readData();
    
private:
    int serial;
};

#endif
#endif
