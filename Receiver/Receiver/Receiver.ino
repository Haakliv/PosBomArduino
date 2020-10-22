#include <RH_ASK.h>
#include "WiFi.h"
#include <HTTPClient.h>

#define BUFSIZE 10

// WiFi Settings
const char* ssid = "Haaklivwifi";
const char* password =  "haakonwifi1";

RH_ASK driver(2000, 18, 19, 0); // ESP8266 or ESP32: do not use pin 11 or 2

void setup(){
  delay(1000);
  Serial.begin(9600);

  WiFi.begin(ssid, password); // Init wifi

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
 
  Serial.print("Connected to the WiFi network with IP: ");
  Serial.println(WiFi.localIP());
    
  if (!driver.init()) // Init radio
    Serial.println("Radio setup failed.");
    Serial.println("Radio activated.");
}

void loop(){
  uint8_t buf[BUFSIZE];
  uint8_t buflen;

  buflen = BUFSIZE;
  if (driver.recv(buf, &buflen)) {
    Serial.print("Received "); Serial.print(buflen,DEC); Serial.write(" bytes:  ");
    buf[buflen]=0;
    Serial.println((char*)buf);         
  }

  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    HTTPClient http;   
 
    http.begin("http://192.168.1.88:8090/");  //Specify destination for HTTP request
    http.addHeader("Content-Type", "text/plain"); //Specify content-type header
 
    int httpResponseCode = http.POST("Hello Bottle, from ESP32");  //Send the actual POST request
 
    if(httpResponseCode>0){
      Serial.println(httpResponseCode);   //Print return code
    } else {
      Serial.print("Error on sending request: ");
      Serial.println(httpResponseCode);
    }
 
   http.end();  //Free resources
  } else {
    Serial.println("Error in WiFi connection");   
  }
 
  delay(5000);  //Send a request every 5 seconds
}
