// Copyright Victor Hurdugaci (http://victorhurdugaci.com). All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE in the project root for license information.

// Remove the following line if you are not using an LCD to display data
#define LCD

#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

#include <ArduinoSerialProtocol.h> 

// The payload that will be sent to the other device
struct SamplePayload {
    int8_t A;
    uint8_t B;
    int16_t C;
    uint16_t D;
} payload;

ArduinoSerialProtocol protocol(&Serial, (uint8_t*)&payload, sizeof(payload));
uint8_t receiveState;

#ifdef LCD
// If using the LCD, you might have to configure the pins to match your setup
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#endif


void setup() 
{
#ifdef LCD
    lcd.begin(20, 4);
#endif

    Serial.begin(9600);

    payload.A = 0;
    payload.B = 0;
    payload.C = 0;
    payload.D = 0;
}

void loop()
{
    receiveState = protocol.receive();

#ifdef LCD
    lcd.clear();
  
    lcd.print(payload.A);

    lcd.setCursor(0,1);
    lcd.print(payload.B);

    lcd.setCursor(0,2);
    lcd.print(payload.C);

    lcd.setCursor(0,3);
    lcd.print(payload.D);
#endif
  
    if (receiveState == ProtocolState::SUCCESS)
    {
        ++payload.A;
        ++payload.B;
        ++payload.C;
        ++payload.D;
    
        protocol.send();
    
#ifdef LCD
        // Revert the payload to display the value that we got, not the one that we sent
        --payload.A;
        --payload.B;
        --payload.C;
        --payload.D;
#endif
    }

    delay(1000);
}

