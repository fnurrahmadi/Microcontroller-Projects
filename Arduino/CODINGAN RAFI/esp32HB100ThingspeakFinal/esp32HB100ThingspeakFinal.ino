#include <WiFi.h>

//SERIAL2 PINS on ESP32
#define RX2 16
#define TX2 17

//WIFI AND THINGSPEAK CONFIGURATIONS
String apiKey = "WTCV226CGGVR2IRF"; //  Enter your Write API key from ThingSpeak
const char *ssid =  "Suparno Fak"; // replace with your wifi ssid and wpa2 key
const char *pass =  "hildebrandgasse2/9";
const char* server = "api.thingspeak.com";
WiFiClient client;

//VARIABLES FOR RECEIVING AN ARRAY OF CHARS
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];
float kph;
boolean newData = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RX2, TX2);
  delay(100);
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
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0
    parseData();
    showParsedData();
    newData = false;
  }
  
  if (client.connect(server,80)) {
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

      Serial.println("Send to Thingspeak");
      
      client.stop();
      Serial.println("Waiting...");
      delay(20000);
      Serial.println("Done Waiting!");
      kph = 0;
    }
  }
  delay(10);
}

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;
  
  while (Serial2.available() > 0 && newData == false) {
    rc = Serial2.read();
    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

void parseData() {      // split the data into its parts using delimiter
  char * strtokIndx; // this is used by strtok() as an index
  
  strtokIndx = strtok(tempChars, ",");
  kph = atof(strtokIndx); //convert to float
}

void showParsedData() {
  Serial.print("kph : ");
  Serial.println(kph);
}
