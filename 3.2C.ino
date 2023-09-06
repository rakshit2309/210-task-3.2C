#include "arduino_secrets.h" 
#include <WiFiNINA.h>
int intense;

char ssid[] = SECRET_SSID;

char pass[] = SECRET_PASSWORD;


WiFiClient client;


char   HOST_NAME[] = "maker.ifttt.com";

String PATH_NAME   = "/trigger/trigger/with/key/dt9bquVD1S1wrzbLv-o87P"; 

String queryString = "?value1=57&value2=25";


void setup() {
  WiFi.begin(ssid, pass);


  Serial.begin(9600);

  while (!Serial);

  if (client.connect(HOST_NAME, 80)) {

    Serial.println("Connected to server");

  }

  else {
    Serial.println("connection failed");
  }

}


void loop() {

  intense = analogRead(A5);
  Serial.println(intense);
  if (intense > 600) {

    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");

    client.println("Host: " + String(HOST_NAME));

    client.println("Connection: close");

    client.println(); 
    while (client.connected()) {

      if (client.available()) {
        char c = client.read();
        Serial.print(c);
      }

    }
    client.stop();
    Serial.println();
    Serial.println("disconnected");

}
}
