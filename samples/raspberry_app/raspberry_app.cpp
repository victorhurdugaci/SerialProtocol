// Copyright Victor Hurdugaci (http://victorhurdugaci.com). All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE in the project root for license information.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>

#include <StreamSerialProtocol.h>

// Change the device, if needed
#define SERIAL_DEVICE "/dev/ttyACM0"

// The structure is maked with __attribute((packed))
// because we don't want any structure padding. Otherwise we might
// send an invalid message to the device.
struct SamplePayload {
    int8_t A;
    uint8_t B;
    int16_t C;
    uint16_t D;
} __attribute__((packed)) payload;

int main() 
{
    int serial = open(
        SERIAL_DEVICE, 
        O_RDWR | O_NOCTTY | O_NDELAY);
 
    if (serial == -1) 
    {
        printf("Failed to open serial port.\n");
        return -1;  
    }

    payload.A = 0;
    payload.B = 0;
    payload.C = 0;
    payload.D = 0;

    // Serial is available so let's configure it
    // All configuration options and explanations here:
    // http://linux.die.net/man/3/termios
    struct termios options;
    tcgetattr(serial, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(serial, TCIFLUSH);
    tcsetattr(serial, TCSANOW, &options); 

    // Create the stream protocol object
    StreamSerialProtocol protocol(serial, (uint8_t*)&payload, sizeof(payload));
    
    uint8_t receiveState;
    
    // We are keeping track of the last received package because
    // from time to time, packages get lost. If we get no packages for 5 seconds
    // we'll retry the last package
    time_t lastPackage = time(NULL);
    time_t now;
    
    while(true)
    {
        receiveState = protocol.receive();
        
        if (receiveState == ProtocolState::SUCCESS)
        {
            printf("-----\nA: %d\nB: %d\nC: %d\nD: %d\n",
                payload.A,
                payload.B,
                payload.C,
                payload.D);
            
            ++payload.A;
            ++payload.B;
            ++payload.C;
            ++payload.D;
            
            protocol.send();
            time(&lastPackage);
        }
    
        time(&now);
        if (difftime(now, lastPackage) > 5)
        {
            printf("Retrying the last package...\n");
            
            // If something went bad, retry the last package 
            protocol.send();
            time(&lastPackage);
        }
    
        sleep(1);
    }

    // This samples will never reach this code but it is here to show
    // how to gracefully close the serial port
    close(serial);
    return 0;
}
