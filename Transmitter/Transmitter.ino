/*
  SimpleSend
  This sketch transmits a short text message using the VirtualWire library
  connect the Transmitter data pin to Arduino pin 12
*/

#include <RH_ASK.h>
RH_ASK driver(2000, 0, 1); // 200bps, TX on D1 , RX on D0 

void setup()
{
    // Initialize the IO and ISR

}

void loop()
{
    char message[] = "hello";
    send(message);
    delay(1000);
}

void send (char *message)
{
  driver.send((uint8_t *)message, strlen(message));
}
