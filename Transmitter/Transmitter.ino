/*
  SimpleSend
  This sketch transmits a short text message using the VirtualWire library
  connect the Transmitter data pin to Arduino pin 12
*/

#include <RH_ASK.h>
RH_ASK driver(2000, 4, 3); // 200bps, TX on D3 (pin 2), RX on D4 (pin 3)

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
