// Copyright Victor Hurdugaci (http://victorhurdugaci.com). All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE in the project root for license information.

#include <SerialProtocol.h>

/* Message format:
    Header        (1 byte)           - Header Byte
    DataLength   (1 byte)            - The size of the payload
    Data         (DataLength bytes)  - Actual payload
    Checksum     (1 byte)            - Message integrity check

    Total message size = (payload size + 3) bytes;
*/

#define HEADER 'S'

// The number of bytes required to read before the actual payload
// is encountered
#define BYTES_TO_PAYLOAD 2

SerialProtocol::SerialProtocol(uint8_t* payload, uint8_t payloadSize)
{
    this->payload = payload;
    this->payloadSize = payloadSize;

    inputBuffer = (uint8_t*)malloc(payloadSize);
}

uint8_t SerialProtocol::send()
{
    if (!serialAvailable())
    {
        // There is no place to send the data
        return ProtocolState::NO_SERIAL;
    }

    uint8_t checksum = payloadSize;

    // Write the header
    sendData(HEADER);
    sendData(payloadSize);

    // Write the payload
    for (int i = 0; i < payloadSize; i++)
    {
        checksum ^= *(payload + i);
        sendData(*(payload + i));
    }

    // Complete with the checksum
    sendData(checksum);

    return ProtocolState::SUCCESS;
}

// This method is blocking while there is data in the serial buffer
uint8_t SerialProtocol::receive()
{
    uint8_t state;
    uint8_t data;

    if (!serialAvailable())
    {
        // Cannot get any data
        return ProtocolState::NO_SERIAL;
    }

    while(true)
    {
        data = readData();

        if (data == -1)
        {
            return bytesRead > 0 ?
                ProtocolState::WAITING_FOR_DATA :
                ProtocolState::NO_DATA;
        }

        if (bytesRead == 0)
        {
            // Look for header
            if (data != HEADER)
            {
                return ProtocolState::NO_DATA;
            }

            ++bytesRead;
            continue;
        }

        if (bytesRead == 1)
        {
            // Look for payload size
            if (data != payloadSize)
            {
                bytesRead = 0;
                return ProtocolState::INVALID_SIZE;
            }

            // The checksum starts with the payload size
            actualChecksum = data;

            ++bytesRead;
            continue;
        }

        // The > check ensures that we don't overflow and
        // that we discard bad messages
        if (bytesRead >= (payloadSize + BYTES_TO_PAYLOAD))
        {
            // We are done with the message. Regardless of the outcome
            // only a new message can come next
            bytesRead = 0;

            // Before we can be fully done, we need the
            // checksum to match
            if (actualChecksum != data)
            {
                return ProtocolState::INVALID_CHECKSUM;
            }

            memcpy(payload, inputBuffer, payloadSize);
            return ProtocolState::SUCCESS;
        }
                
        inputBuffer[bytesRead - BYTES_TO_PAYLOAD] = data;
        actualChecksum ^= data;
        
        ++bytesRead;
    }
}
