// Copyright Victor Hurdugaci (http://victorhurdugaci.com). All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE in the project root for license information.

#include <SerialProtocol.h>

/* Message format:
    Start        (1 byte)            - Start Byte
    DataLength   (1 byte)            - The size of the payload
    Data         (DataLength bytes)  - Actual payload
    Checksum     (1 byte)            - Message integrity check

    Total message size = (payload size + 3) bytes;
    */

const uint8_t START_BYTE = 'S';

SerialProtocol::SerialProtocol(HardwareSerial* serial, uint8_t* payload, uint8_t payloadSize)
{
    this->payload = payload;
    this->payloadSize = payloadSize;

    inputBuffer = (uint8_t*)malloc(payloadSize);
    resetInput();

    setSerial(serial);
}

void SerialProtocol::setSerial(HardwareSerial* serial)
{
    this->serial = serial;
}

uint8_t SerialProtocol::send()
{
    if (serial == NULL)
    {
        // There is no place to send the data
        return ProtocolState::NO_SERIAL;
    }

    uint8_t checksum = payloadSize;

    // Write the header
    serial->write(START_BYTE);
    serial->write(payloadSize);

    // Write the payload
    for (int i = 0; i < payloadSize; i++)
    {
        checksum ^= *(payload + i);
        serial->write(*(payload + i));
    }

    // Complete with the checksum
    serial->write(checksum);

    return ProtocolState::SUCCESS;
}

// This method is blocking while there is data in the serial buffer
uint8_t SerialProtocol::receive()
{
    uint8_t state;
    char data;

    if (serial == NULL)
    {
        // There is no place to send the data
        return ProtocolState::NO_SERIAL;
    }

    state = canReadMessageBytes();
    if (state != ProtocolState::SUCCESS)
    {
        return state;
    }

    while (bytesRead <= payloadSize)
    {
        data = serial->read();

        if (data == -1) 
        {
            // No more data
            return ProtocolState::WAITING_FOR_DATA;
        }

        if (bytesRead >= payloadSize) 
        {
            // We are done with the payload

            // Before we can be done, we need the
            // checksum to match
            if (actualChecksum != data)
            {
                resetInput();
                return ProtocolState::INVALID_CHECKSUM;
            }

            resetInput();

            memcpy(payload, inputBuffer, payloadSize);
            return ProtocolState::SUCCESS;
        }

        inputBuffer[bytesRead++] = data;
        actualChecksum ^= data;
    }

}

void SerialProtocol::resetInput()
{
    bytesRead = 0;
    actualChecksum = 0;
}

uint8_t SerialProtocol::canReadMessageBytes()
{
    char data;

    if (bytesRead > 0)
    {
        // We are in a message but there might be no data to read
        return serial->available() > 0 ?
            ProtocolState::SUCCESS :
            ProtocolState::WAITING_FOR_DATA;
    }

    // If we get here, we don't have a message yet.
    // Block until we can either start reading a message
    // or there is no more data
    while (true)
    {
        data = serial->peek();

        if (data == -1)
        {
            // Nothing to do, empty buffer
            return ProtocolState::NO_DATA;
        }

        if (data != START_BYTE)
        {
            // Discard the data, not interesting
            serial->read();
            continue;
        }

        // We have a possible known message but first let's see if
        // there is enough data to start reading.
        // We need at least 3 bytes (START_BYTE, length, one extra byte)
        // otherwise we might skip messages
        if (serial->available() < 3)
        {
            return ProtocolState::WAITING_FOR_DATA;
        }

        // We have the needed bytes so we can read the header

        // Discard the start byte
        serial->read();

        if (serial->read() != payloadSize)
        {
            // We are trying to read something that is
            // of different size that what the protocol
            // expects
            return ProtocolState::INVALID_SIZE;
        }

        actualChecksum = payloadSize;

        // Good to go, you can start reading
        return ProtocolState::SUCCESS;
    }
}