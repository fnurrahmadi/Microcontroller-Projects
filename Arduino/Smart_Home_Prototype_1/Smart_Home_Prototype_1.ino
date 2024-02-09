//--------------------------LIBRARIES----------------------------

#include <Stepper.h>
//#include <Servo.h>
#include <SoftwareSerial.h> // BLUETOOTH SERIAL CONNECTION
#include <RBD_Timer.h> // A BETTER REPLACEMENT FOR DELAY()

//--------------------------VARIABLES----------------------------

// RBD TIMER - WATER PUMP
RBD::Timer pumpStart(10000);
RBD::Timer pumpDelay(5000);
RBD::Timer garageDelay(4000);

// BLUETOOTH SERIAL
SoftwareSerial android(52, 53); // RX, TX (SWITCHED)
/*const byte numChars = 32; //  MAXIMUM NUMBER OF CHARACTERS 
char BluetoothData[numChars]; // DATA FROM BLUETOOTH IN ARRAY
boolean newData = false;*/
String BluetoothData;

// RELAYS
int relay1 = 39; // FRONT LIGHTS
int relay2 = 38; // LIVING ROOM LIGHTS
int relay3 = 37; // WATER PUMP
int relay4 = 36; // EXHAUST FAN
//int relay5 = 34; // SOLENOID DOOR //---RASPBERRY PI
int relay6 = 35; // BED ROOM LIGHTS

// MOTORS
// STEPPER MOTOR - ULN2003A - GARAGE DOOR
const int steps = 1;
Stepper garagedoor(steps, 9, 11, 10, 12);

// DC MOTOR - L293D - AUTO ROOF
//const int motorDCenA = 2;
const int motorDCin1 = 3;
const int motorDCin2 = 4;

// SERVO MOTOR - FRONT DOOR
//int frontdoor = 5; //---RASPBERRY PI

// LED - TELEVISION
const int ledPin = 13;

// INPUTS
int waterPin = 26; // RAIN SENSOR
int gasPin = 25; // KITCHEN GAS SENSOR
int ldrPin = 24; // LDR - LIGHT SENSOR
int limitswitch1 = 23; // AUTO ROOF LIMIT SWITCH 1
int limitswitch2 = 22; // AUTO ROOF LIMIT SWITCH 2

//--------------------------FUNCTIONS----------------------------

// FRONT LIGHT CONDITIONS
void frontlights() {
  if (digitalRead(ldrPin) == HIGH) { // DARK
    digitalWrite(relay1, HIGH);
  }
  else { // LIGHT
    digitalWrite(relay1, LOW);
  }
}

// ACTIVATES WATER PUMP
void pumpon() {
  digitalWrite(relay3, HIGH);
}

// DEACTIVATES WATER PUMP
void pumpoff() {
  digitalWrite(relay3, LOW);
}

// WATER PUMP CONDITIONS
void waterpump() {
  if(pumpDelay.isExpired()) {
    pumpon();
    pumpStart.restart();
    if(pumpStart.isExpired()) {
      pumpoff();
      pumpDelay.restart();
    }
  }
}

// GAS DETECTION CONDITIONS - EXHAUST FAN
void gasdetection() {
  int gasValue = digitalRead(gasPin);
  //Serial.println(gasValue);
  if (gasValue > 0) {
    digitalWrite(relay4, HIGH);
  } else {
    digitalWrite(relay4, LOW);
  }
}

// OPENS ROOF
void openroof() {
  if (digitalRead(limitswitch1) == LOW) {
    digitalWrite(motorDCin1, HIGH);
    digitalWrite(motorDCin2, LOW);
  }
  else {
    stoproof();
  }
}
// CLOSES ROOF
void closeroof() {
  if (digitalRead(limitswitch2) == LOW) {
    digitalWrite(motorDCin1, LOW);
    digitalWrite(motorDCin2, HIGH);
  }
  else {
    stoproof();
  }
}

// STOPS ROOF FROM CLOSING/OPENING
void stoproof() {
  digitalWrite(motorDCin1, LOW);
  digitalWrite(motorDCin2, LOW);
}

// AUTO ROOF CONDITIONS - DAYLIGHT AND RAIN
void autoroof() {
  if (digitalRead(ldrPin) == HIGH) { // DARK
    closeroof();
  }
  else {
    if (digitalRead(waterPin) == HIGH) { // RAIN
      closeroof();
    }
    else { // NOT DARK + NOT RAINING
      openroof();
    }
  }
}

//-------------------------VOICE CONTROL-------------------------

// LIVING ROOM LIGHT CONDITIONS - VOICE CONTROL
void livingroomlights() {
  if (BluetoothData == "living room on") {
    digitalWrite(relay2, HIGH); 
  }
  else if (BluetoothData == "living room off") {
    digitalWrite(relay2, LOW);
  }
}

// BED ROOM LIGHT CONDITIONS - VOICE CONTROL
void bedroomlights() {
  if (BluetoothData == "bed room on") {
    digitalWrite(relay6, HIGH); 
  }
  else if (BluetoothData == "bed room off") {
    digitalWrite(relay6, LOW);
  }
}

// OPENS GARAGE DOOR
void opengarage() {
  garagedoor.step(steps);
}

// CLOSES GARAGE DOOR
void closegarage() {
  garagedoor.step(-steps);
}

// STOPS GARAGE DOOR
void stopgarage() {
  garagedoor.step(0);
}

// GARAGE DOOR CONDITIONS - VOICE CONTROL
void garagecontrol() {
  if (BluetoothData == "open garage") {
    garageDelay.restart();
    if (garageDelay.isActive()) {
      opengarage();
    }
    stopgarage();
  }
  else if (BluetoothData == "close garage") {
    garageDelay.restart();
    if (garageDelay.isActive()) {
      closegarage();
    }
    stopgarage();
  }
}

// GARAGE DOOR CONDITIONS - BUTTON CLICK
void garagecontrol2() {
  if (BluetoothData == "1") {
    opengarage();
  }
  else if (BluetoothData == "2") {
    closegarage();
  }
  else if (BluetoothData == "A") {
    stopgarage();
  }
}

// TURNS ON TELEVISION
void televisionon() {
  digitalWrite(ledPin, HIGH);
}

// TURNS OFF TELEVISION
void televisionoff() {
  digitalWrite(ledPin, LOW);
}

// TELEVISION CONDITIONS - VOICE CONTROL
void televisioncontrol() {
  if (BluetoothData == "television on") {
    televisionon();
  }
  else if (BluetoothData == "television off") {
    televisionoff();
  }
}

//---------------------BLUETOOTH TRANSMISSION--------------------

// RECEIVING BLUETOOTH DATA FROM ANDROID APP
/*void receivedata() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (android.available() > 0 && newData == false) {
    rc = android.read();

    if (rc != endMarker) {
      BluetoothData[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      BluetoothData[ndx] = '\0'; // TERMINATE THE STRING
      ndx = 0;
      newData = true;
    }
  }
}*/

// PRINTING DATA RECEIVED AND READYING FOR NEXT DATA
void printdata() {
//  if (newData == true) {
  if (BluetoothData.length() > 0) {
    Serial.println("Voice Commmand Received: ");
    Serial.println(BluetoothData);
    //newData = false;
  }
}

// RECEIVING BLUETOOTH DATA
void receivebluetooth() {
  while(android.available()) {
  //while(Serial.available()) {
    delay(10);
    char c = android.read();
    //char c = Serial.read();
    if (c == '#') {
      break;
    }
    BluetoothData += c;
  }
  bluetoothcommands();
}

// BLUETOOTH DATA CONDITIONS/COMMANDS
void bluetoothcommands() {
  if (BluetoothData.length() > 0) { 
    Serial.println(BluetoothData);
    livingroomlights();
    bedroomlights();
    garagecontrol();
    garagecontrol2();
    televisioncontrol();
    
  }
  BluetoothData="";
}

//--------------------------VOID SETUP---------------------------

void setup() {
  Serial.begin(9600);
  //android.begin(38400); // BLUETOOTH SOFTWARESERIAL CONNECTION
  android.begin(9600);
  garagedoor.setSpeed(60);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  //pinMode(relay5, OUTPUT); //---RASPBERRY PI
  pinMode(relay6, OUTPUT);
  //pinMode(frontdoor, OUTPUT); //---RASPBERRY PI
  pinMode(motorDCin1, OUTPUT);
  pinMode(motorDCin2, OUTPUT);
  pinMode(ledPin, OUTPUT);

  pinMode(waterPin, INPUT);
  pinMode(gasPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(limitswitch1, INPUT);
  pinMode(limitswitch2, INPUT);
}

//---------------------------VOID LOOP---------------------------

void loop() {
  // AUTOMATION FUNCTIONS
  frontlights();
  gasdetection();
  waterpump();
  autoroof();
  
  // VOICE CONTROL
  //garagecontrol(); //---VOICE CONTROL
  //receivedata();
  //printdata();
  receivebluetooth();
  //bluetoothcommands();
}
