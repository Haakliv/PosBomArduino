#include <RH_ASK.h>



/*
  SimpleReceive
  This sketch  displays text strings received using VirtualWire
  Connect the Receiver data pin to Arduino pin 11
*/

byte message[RH_ASK_MAX_MESSAGE_LEN];    // a buffer to hold the incoming messages
byte msgLength = RH_ASK_MAX_MESSAGE_LEN; // the size of the message

RH_ASK driver(2000, 4, 3); // 200bps, TX on D3 (pin 2), RX on D4 (pin 3)


void setup()
{
    Serial.begin(9600);
    Serial.println("Ready");

}

void loop()
{
    if (driver.recv(message, &msgLength)) // Non-blocking
    {
        Serial.print("Got: ");
    for (int i = 0; i < msgLength; i++)
    {
        Serial.write(message[i]);
    }
    Serial.println();
    }
}
