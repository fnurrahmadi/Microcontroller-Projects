//---------------------LIBRARIES-------------------------

#include <Servo.h>
#include "A4988.h"
#include <BTS7960.h>
#include <Wire.h>
#include "PCA9685.h"
#include <SoftwareSerial.h>

//---------------------PINS------------------------------

#define R_PWM_KIRI 11
#define R_EN_KIRI 13
#define R_PWM_KANAN 6
#define R_EN_KANAN 8

#define L_PWM_KIRI 10
#define L_EN_KIRI 12
#define L_PWM_KANAN 5
#define L_EN_KANAN 7

#define gripCh 0  // 180 kunci, 0 buka
#define wristCh 1  // 90 normal
#define elbowCh 2 // -

#define DIRZ 48 // dituker gamau jadi pesawat 
#define STEPZ 49 // dituker gamau jadi pesawat
#define MS1Z 53 // dituker gamau jadi pesawat
#define MS2Z 52 // dituker gamau jadi pesawat
#define MS3Z 51 // dituker gamau jadi pesawat
#define ENZ 50 // dituker gamau jadi pesawat

#define RX1 2
#define TX1 3

//---------------------VARIABLES-------------------------

int z = 0; // save koordinat sebelum
int stepperSteps = 200;
int stepperRPM = 300;
int stepperCM = -220; // ~0,5 CENTIMETER

int gripPos = 0; // posisi buka
int wristPos = 0; // posisi down
int elbowPos = 90;
int chPos = 5;

int midPos = 90;
int T1Pos = 20;
int T2Pos = 10;
int T3Pos = 0;

int ZTop = 0;
int ZBot = 20;

int motorSpeedKiri = -120; //(0-127 cw, 128-255 ccw)
int motorSpeedKanan = 124;

int joystickData;

A4988 stepperZ(stepperSteps, DIRZ, STEPZ, MS1Z, MS2Z, MS3Z);
PCA9685 driver;
BTS7960 motorKiri(R_PWM_KIRI, L_PWM_KIRI, L_EN_KIRI, R_EN_KIRI);
BTS7960 motorKanan(R_PWM_KANAN, L_PWM_KANAN, L_EN_KANAN, R_EN_KANAN);
SoftwareSerial hc06(RX1, TX1); // RX, TX

// PCA9685 outputs = 12-bit = 4096 steps
// 2.5% of 20ms = 0.5ms ; 12.5% of 20ms = 2.5ms
// 2.5% of 4096 = 102 steps; 12.5% of 4096 = 512 steps
PCA9685_ServoEvaluator pwmGrip(102, 310, 505); // (0deg, 90deg, 180deg)
PCA9685_ServoEvaluator pwmWrist(102, 310, 505); // (0deg, 90deg, 180deg)
PCA9685_ServoEvaluator pwmElbow(102, 310, 505); // (0deg, 90deg, 180deg)

//----------------------SETUP----------------------------

void setup() {
  Wire.begin();                 // Wire must be started first
  Wire.setClock(400000);        // Supported baud rates are 100kHz, 400kHz, and 1000kHz
  driver.resetDevices();        // Software resets all PCA9685 devices on Wire line
  driver.init(B000000);         // Address pins A5-A0 set to B000000
  driver.setPWMFrequency(50);   // Set frequency to 50Hz

  hc06.begin(9600);
  //Serial.begin(9600);

  stepperZ.begin(stepperRPM, 1);
  stepperZ.setEnableActiveState(LOW);

  motorKiri.enable();
  motorKanan.enable();

  driver.setChannelPWM(gripCh, pwmGrip.pwmForAngle(gripPos));
  driver.setChannelPWM(wristCh, pwmWrist.pwmForAngle(wristPos));
  driver.setChannelPWM(elbowCh, pwmElbow.pwmForAngle(elbowPos));
}

//-----------------------LOOP----------------------------

void loop() {
  if (hc06.available()) {
    joystickData = hc06.read();
    //Serial.println(joystickData);
    joystickOptions();
  }
}

//----------------------JOYSTICK-------------------------

void joystickOptions() {
  // MOVEMENT - DPAD
  if (joystickData == '0') {
    roam(0, 0);
  }
  else if (joystickData == '1') {
    roam(motorSpeedKiri, motorSpeedKanan);
  }
  else if (joystickData == '2') {
    roam(motorSpeedKiri, 0);
  }
  else if (joystickData == '3') {
    roam(-motorSpeedKiri, -motorSpeedKanan);
  }
  else if (joystickData == '4') {
    roam(0, motorSpeedKanan);
  }

  // PELAN2 CLUB
  else if (joystickData == '5') {
    roam((motorSpeedKiri / 3), (motorSpeedKanan / 3));
  }
  else if (joystickData == '7') {
    roam((-motorSpeedKiri / 3), (-motorSpeedKanan / 3));
  }

  // SHARP MOVEMENT
  else if (joystickData == '6') {
    roam(motorSpeedKiri / 4 , -motorSpeedKanan / 4);
  }
  else if (joystickData == '8') {
    roam(-motorSpeedKiri / 4 , motorSpeedKanan / 4);
  }

  // T1
  else if (joystickData == 'A') {
    //grip open
    gripStep(chPos);
    //wrist up
    wristStep(chPos);
    //elbow left (customized)
    elbowStep(T1Pos);
    //wrist down
    wristStep(-chPos);
    //grip close
    gripStep(-chPos);
    //wrist up
    wristStep(chPos);
    //elbow right (customized)
    elbowStep(midPos);
    //stepper down
    cartesian(20);
    //wrist down
    wristStep(-chPos);
    //grip open
    gripStep(chPos);
    //stepper up
    cartesian(0);
  }

  // T2
  else if (joystickData == 'B') {
    //grip open
    gripStep(chPos);
    //wrist up
    wristStep(chPos);
    //elbow left (customized)
    elbowStep(T2Pos);
    //wrist down
    wristStep(-chPos);
    //grip close
    gripStep(-chPos);
    //wrist up
    wristStep(chPos);
    //elbow right (customized)
    elbowStep(midPos);
    //stepper down
    cartesian(20);
    //wrist down
    wristStep(-chPos);
    //grip open
    gripStep(chPos);
    //stepper up
    cartesian(0);
  }

  // T3
  else if (joystickData == 'C') {
    //grip open
    gripStep(chPos);
    //wrist up
    wristStep(chPos);
    //elbow left (customized)
    elbowStep(T3Pos);
    //wrist down
    wristStep(-chPos);
    //grip close
    gripStep(-chPos);
    //wrist up
    wristStep(chPos);
    //elbow right (customized)
    elbowStep(midPos);
    //stepper down
    cartesian(20);
    //wrist down
    wristStep(-chPos);
    //grip open
    gripStep(chPos);
    //stepper up
    cartesian(0);
  }

  // C1
  else if (joystickData == 'a') {
    //grip open
    gripStep(chPos);
    //stepper down
    cartesian(20);
    //grip close
    gripStep(-chPos);
    //wrist up
    wristStep(chPos);
    //stepper up
    cartesian(0);
    //elbow left (customized)
    elbowStep(T3Pos);
    //wrist down
    wristStep(-chPos);
    //grip open
    gripStep(chPos);
    //wrist up
    wristStep(chPos);
    //elbow right (customized)
    elbowStep(midPos);
    //wrist down
    wristStep(-chPos);
  }

  // C2
  else if (joystickData == 'b') {
    //grip open
    gripStep(chPos);
    //stepper down
    cartesian(20);
    //grip close
    gripStep(-chPos);
    //wrist up
    wristStep(chPos);
    //stepper up
    cartesian(0);
    //elbow left (customized)
    elbowStep(T2Pos);
    //wrist down
    wristStep(-chPos);
    //grip open
    gripStep(chPos);
    //wrist up
    wristStep(chPos);
    //elbow right (customized)
    elbowStep(midPos);
    //wrist down
    wristStep(-chPos);
  }

  // C3
  else if (joystickData == 'c') {
    //grip open
    gripStep(chPos);
    //stepper down
    cartesian(20);
    //grip close
    gripStep(-chPos);
    //wrist up
    wristStep(chPos);
    //stepper up
    cartesian(0);
    //elbow left (customized)
    elbowStep(T1Pos);
    //wrist down
    wristStep(-chPos);
    //grip open
    gripStep(chPos);
    //wrist up
    wristStep(chPos);
    //elbow right (customized)
    elbowStep(midPos);
    //wrist down
    wristStep(-chPos);
  }
}

//----------------------FUNCTIONS------------------------

// MOVEMENT FUNCTION
void roam(int pwmkiri, int pwmkanan) {
  motorKiri.setSpeed(pwmkiri);
  motorKanan.setSpeed(pwmkanan);
}

// SERVO FUNCTIONS
void gripStep(int pos) {
  gripPos += pos;
  driver.setChannelPWM(gripCh, pwmGrip.pwmForAngle(gripPos));
  if (gripPos < 0) {
    gripPos = 0;
  }
  if (gripPos > 180) {
    gripPos = 180;
  }
  //delay(10);
}

void wristStep(int pos) {
  wristPos += pos;
  driver.setChannelPWM(wristCh, pwmWrist.pwmForAngle(wristPos));
  if (wristPos < 0) {
    wristPos = 0;
  }
  if (wristPos > 90) {
    wristPos = 90;
  }
  //delay(10);
}

/*void elbowStep(int pos) {
  elbowPos += pos;
  driver.setChannelPWM(elbowCh, pwmElbow.pwmForAngle(elbowPos));
  if (elbowPos < 0) {
    elbowPos = 0;
  }
  if (elbowPos > 90) {
    elbowPos = 90;
  }
  //delay(10);
}*/

void elbowStep(int dest){
  if (elbowPos > dest){
    elbowPos -= chPos;
    driver.setChannelPWM(elbowCh, pwmWrist.pwmForAngle(elbowPos));
  }
  else {
    elbowPos += chPos;
    driver.setChannelPWM(elbowCh, pwmWrist.pwmForAngle(elbowPos));
  }
}

// CARTESIAN FUNCTIONS
void cartesian(int Z1) {
  int deltaZ = Z1 - z;
  stepperZ.rotate(deltaZ * stepperCM);
  z = Z1;
}
