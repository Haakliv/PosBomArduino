// Kode for bombrikke, sender en streng over RFID med RadioHead-biblioteket
// Basert på RadioHead eksempel

#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#endif

//RH_ASK driver;
RH_ASK driver(2000, 4, 5, 0);

void setup(){
#ifdef RH_HAVE_SERIAL
    Serial.begin(9600);
#endif
    if (!driver.init())
#ifdef RH_HAVE_SERIAL // Sjekker om driverent er initialisert
         Serial.println("Initialisering feilet");
#else
  ;
#endif
}

void loop(){
    const char *msg = "11111113"; // Melding som skal sendes

    driver.send((uint8_t *)msg, strlen(msg)); // Sender melding
    driver.waitPacketSent(); // Venter til melding er sendt
    Serial.println("Melding sendt");
    delay(5000); // Venter 1 sekund
}
