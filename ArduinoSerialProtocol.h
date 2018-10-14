// Copyright Victor Hurdugaci (http://victorhurdugaci.com). All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE in the project root for license information.

#ifdef ARDUINO
#ifndef ARDUINOSERIALPROTOCOL_H
#define ARDUINOSERIALPROTOCOL_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include <SerialProtocol.h>

class ArduinoSerialProtocol : public SerialProtocol
{
public:
    ArduinoSerialProtocol(HardwareSerial*, uint8_t*, uint8_t);

    void setSerial(HardwareSerial*);
    
protected:
    bool serialAvailable();

    void sendData(uint8_t data);
    uint8_t readData();
    
private:
    HardwareSerial *serial;
};

#endif
#endif
