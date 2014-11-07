// Copyright Victor Hurdugaci (http://victorhurdugaci.com). All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE in the project root for license information.

#include "Arduino.h";
#include "HardwareSerial.h"

struct ProtocolState 
{
    enum Enum {
        // The serial object was not set
        NO_SERIAL = 0,

        // There is not (enought) data to process
        NO_DATA = 1,

        // The size of the received payload doesn't match the expected size
        INVALID_SIZE = 2,

        // The object was received but it is not the same as one sent
        INVALID_CHECKSUM = 3,

        // The object is being received but the buffer doesn't have all the data
        WAITING_FOR_DATA = 4,

        // The operation succeeded
        SUCCESS = 5
    };
};

class SerialProtocol
{
public:
    SerialProtocol(HardwareSerial*, uint8_t*, uint8_t);

    // Sets the serial object
    void setSerial(HardwareSerial*);

    // Sends the current payload
    //
    // Returns a ProtocolState enum value
    uint8_t send();

    // Tries to receive the payload from the
    // current available data
    // Will replace the payload if the receive succeeds
    // 
    // Returns a ProtocolState enum value
    uint8_t receive();

private:
    void resetInput();
    uint8_t canReadMessageBytes();

    HardwareSerial *serial;

    uint8_t* payload;
    uint8_t payloadSize;

    uint8_t* inputBuffer;
    uint8_t bytesRead;

    uint8_t actualChecksum;
};