//#include <SoftwareSerial.h>
#include <Stepper.h>
#include <RBD_Timer.h>

//SoftwareSerial android(52, 53); // RX, TX

const int steps = 200;
Stepper garagedoor(steps, 9, 11, 10, 12);
RBD::Timer garageDelay(4000);
String voice;
int RED = 2;
int GREEN = 7;
int YELLOW = 4;

void setup() {
//android.begin(38400);
Serial.begin(9600);
pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(YELLOW, OUTPUT);
garagedoor.setSpeed(60);
}
void loop() {
  while(Serial.available()) {
delay(10);
char c=Serial.read();
if(c=='#')
{break; }
voice += c;
}
if (voice.length() > 0) {
Serial.println(voice);

  if (voice == "open") {
    garageDelay.restart();
    opengarage();
    if (garageDelay.isExpired()) {
      stopgarage();
    }
  }
  else if (voice == "close") {
    garageDelay.restart();
    opengarage();
    if (garageDelay.isExpired()) {
      stopgarage();
    }
  }
  else if (voice == "green on") {
    digitalWrite(GREEN, HIGH);
  }
  else if (voice == "green off") {
    digitalWrite(GREEN, LOW);
  } 

voice="";
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


