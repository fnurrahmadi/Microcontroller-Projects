#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

SoftwareSerial esp(D5, D6); //RX, TX

String apiKey = "WTCV226CGGVR2IRF"; //  Enter your Write API key from ThingSpeak
const char *ssid =  "Suparno Fak"; // replace with your wifi ssid and wpa2 key
const char *pass =  "hildebrandgasse2/9";
const char* server = "api.thingspeak.com";

WiFiClient client;

double kph;

void setup() {
  // put your setup code here, to run once:
  esp.begin(115200);
  Serial.begin(115200);
  delay(10);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  // put your main code here, to run repeatedly:
  //NERIMA DATA DARI ARDUINO DULU

    //PENGIRIMAN DATA KE THINGSPEAK/CLOUD
    //BUILD STRING UNTUK DIKIRIM
  if (client.connect(server,80))
  {
    if (esp.available())
    {
      kph = esp.read();
      Serial.println(kph);
      
      if (kph >= 10) {
        String postStr = apiKey;
        postStr +="&field1=";
        postStr += String(kph);
        postStr += "\r\n\r\n";
      
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(postStr.length());
        client.print("\n\n");
        client.print(postStr);
        Serial.print("kph: ");
        Serial.println(kph);
        Serial.println("Send to Thingspeak");
        
        client.stop();
        Serial.println("Waiting...");
        delay(20000);
        kph = 0;
        Serial.println("Done Waiting!");
      }
    } 
  }
}
