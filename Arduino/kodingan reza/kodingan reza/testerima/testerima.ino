#include <SoftwareSerial.h>

SoftwareSerial nodeSerial(D5, D6);

// Example 5 - Receive with start- and end-markers combined with parsing

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

//============

void setup() {
  Serial.begin(115200);
  nodeSerial.begin(115200);
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
