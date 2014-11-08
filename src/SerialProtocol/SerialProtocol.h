// Copyright Victor Hurdugaci (http://victorhurdugaci.com). All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE in the project root for license information.

#ifndef SERIALPROTOCOL_H
#define SERIALPROTOCOL_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct ProtocolState 
{
    enum Enum 
    {
        // The serial object was not set
        NO_SERIAL = 0,

         // The operation succeeded
        SUCCESS = 1,

        // There is not (enought) data to process
        NO_DATA = 2,
        
         // The object is being received but the buffer doesn't have all the data
        WAITING_FOR_DATA = 3,

        // The size of the received payload doesn't match the expected size
        INVALID_SIZE = 4,

        // The object was received but it is not the same as one sent
        INVALID_CHECKSUM = 5
    };
};

class SerialProtocol
{
public:
    SerialProtocol(uint8_t*, uint8_t);

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

protected:
    virtual bool serialAvailable() = 0;

    virtual void sendData(uint8_t data) = 0;
    virtual uint8_t readData() = 0;

private:
    uint8_t* payload;
    uint8_t payloadSize;

    uint8_t* inputBuffer;
    uint8_t bytesRead;

    uint8_t actualChecksum;
};

#endif
