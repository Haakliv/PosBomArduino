#include <RH_ASK.h>

RH_ASK driver(2000, 18, 19, 0); // ESP8266 or ESP32: do not use pin 11 or 2

void setup()
{
    delay(1000);
    Serial.begin(9600); 
    if (!driver.init())
         Serial.println("no radio");
   Serial.println("Radio activated");
}

#define BUFSIZE 10

void loop()
{
    uint8_t buf[BUFSIZE];
    uint8_t buflen;

    buflen = BUFSIZE;
    if (driver.recv(buf, &buflen)) 
    {
      Serial.print("Received "); Serial.print(buflen,DEC); Serial.write(" bytes:  ");
      buf[buflen]=0;
      Serial.println((char*)buf);         
    }
}
