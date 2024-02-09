#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

SoftwareSerial nodeSerial(D5, D6);

String apiKey = "Y8WL1O1CTDWTQTCU";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "demus";     // replace with your wifi ssid and wpa2 key
const char *pass =  "demusdwi4";
const char* server = "api.thingspeak.com";

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

// variables to hold the parsed data
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
float floatFromPC = 0.0;

int BPM, IBI;
float suhu;

boolean newData = false;

WiFiClient client;

//============

void setup() {
  Serial.begin(115200);
  nodeSerial.begin(115200);
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

//============

void loop() {
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0
    parseData();
    showParsedData();
    kirimts();
    newData = false;
  }
  delay(1000);
}

//============

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;


  while (nodeSerial.available() > 0 && newData == false) {
    rc = nodeSerial.read();
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

//============

void parseData() {      // split the data into its parts

  char * strtokIndx; // this is used by strtok() as an index

  // strtokIndx = strtok(tempChars,",");      // get the first part - the string
  // strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC

  strtokIndx = strtok(tempChars, ","); // get the first part - the string
  suhu = atof(strtokIndx);     // convert this part to an float

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  BPM = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  IBI = atoi(strtokIndx);     // convert this part to an integer

  // strtokIndx = strtok(NULL, ",");
  // floatFromPC = atof(strtokIndx);     // convert this part to a float

}

//============

void showParsedData() {
  Serial.print("suhuF ");
  Serial.println(suhu);
  Serial.print("BPM ");
  Serial.println(BPM);
  Serial.print("IBI ");
  Serial.println(IBI);
}

void kirimts() {
  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(suhu);
    postStr +="&field2=";
    postStr += String(BPM);
    postStr +="&field3=";
    postStr += String(IBI);    
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.println(postStr);
    Serial.println(" Send to Thingspeak.");
    client.stop();
    Serial.println("Kirim sukses tunggu delay buat kirim selanjutnya");

    // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
    delay(10000);
  }
  else Serial.println("gabisa konek ke thingspeak");
}
