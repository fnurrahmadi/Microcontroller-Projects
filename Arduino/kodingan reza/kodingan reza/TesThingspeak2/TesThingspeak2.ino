#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

SoftwareSerial nodemcuSerial(D5, D6); // RX, TX

String apiKey = "G2QMWNKM7S4KEKEJ";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "UGMURO-2";     // replace with your wifi ssid and wpa2 key
const char *pass =  "makaroningehe";
const char* server = "api.thingspeak.com";

WiFiClient client;

void setup()
{
  nodemcuSerial.begin(115200);
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

  if (Serial.available()){
  data = Serial.read();
  Serial.println(data);
  }

  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(data);
    //postStr +="&field2=";
    //postStr += String(h);
    //postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Temperature: ");
    Serial.print(data);
    Serial.println(" Send to Thingspeak.");
  }
  client.stop();

  Serial.println("Waiting...");

  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10000);
}
