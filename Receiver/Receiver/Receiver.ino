// Program som kobler til internett, mottar data fra bombrikke
// og sender en HTTP POST request til nettsiden

#include <RH_ASK.h>
#include "WiFi.h"
#include <HTTPClient.h>

#define BUFSIZE 10 // Lengde på data vi mottar

// WiFi-Instillinger
const char* ssid = "Haaklivwifi";
const char* password = "haakonwifi1";

RH_ASK driver(2000, 18, 19, 0); // Bruker pin 18 og 19 paa ESP, 2000 baud rate

void setup(){
  delay(1000); // Venter ett sekund paa at ESP skal kunne settes opp
  Serial.begin(9600);

  WiFi.begin(ssid, password); // Init wifi

  while (WiFi.status() != WL_CONNECTED) { // Venter til koblet til
    delay(500);
    Serial.println("Kobler til WiFi...");
  }
 
  Serial.print("Koblet til internett med IP: ");
  Serial.println(WiFi.localIP());
    
  if (!driver.init()) // Init radio
    Serial.println("Radiooppsett feilet.");
    Serial.println("Radio aktivert.");

  char incoming = 0;
  Serial.println("Skriv noe for aa starte programmet.");
  while (true) {
    if (Serial.available() > 0) {
      // read the incoming:
      incoming = Serial.read();
      // say what you got:
      Serial.println(incoming);   
      if (incoming != 0) {
        Serial.println("Starter programmet...");
        break;
      }
    }
  }
}

void loop(){
  uint8_t buf[BUFSIZE];
  uint8_t buflen;
  
  buflen = BUFSIZE;
  if (driver.recv(buf, &buflen)) { // Hvis mottatt data
    Serial.print("Mottatt "); Serial.print(buflen,DEC); Serial.write(" bytes:  ");
    buf[buflen]=0;
    Serial.println((char*)buf);  
    if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    HTTPClient http;   

    http.begin("https://gruppe13.innovasjon.ed.ntnu.no/bomstasjon/");  //Nettside som skal kobles til
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Setter format paa http request

    char *postBuf = (char*)buf;
    String postStr = "id=";
    postStr += postBuf; // Slaar sammen buffer og post-tekst
 
    int httpResponseCode = http.POST(postStr); // Sender POST Request
 
    if(httpResponseCode>0){
      Serial.println(httpResponseCode);   //Print http respons kode
    } else {
      Serial.print("Request feilet: ");
      Serial.println(httpResponseCode);
    }
 
   http.end();  //Free resources
  } else {
    Serial.println("Feil med WiFi-kommunikasjon");   
  }       
  }
  delay(5000);  //Send a request every 5 seconds
}
