#include <Wire.h>
#include "PCA9685.h"

#define gripCh 0  // 180 kunci, 0 buka
#define wristCh 1  // 90 normal
#define elbowCh 2 // -

int gripPos = 0; // posisi buka
int wristPos = 0; // posisi down
int elbowPos = 90;
int chPos = 5;

int midPos = 90;
int T1Pos = 20;
int T2Pos = 10;
int T3Pos = 0;

PCA9685 driver;
PCA9685_ServoEvaluator pwmGrip(102, 310, 505); // (0deg, 90deg, 180deg)
PCA9685_ServoEvaluator pwmWrist(102, 310, 505); // (0deg, 90deg, 180deg)
PCA9685_ServoEvaluator pwmElbow(102, 310, 505); // (0deg, 90deg, 180deg)

void setup() {
  // put your setup code here, to run once:
  Wire.begin();                 // Wire must be started first
  Wire.setClock(400000);        // Supported baud rates are 100kHz, 400kHz, and 1000kHz
  driver.resetDevices();        // Software resets all PCA9685 devices on Wire line
  driver.init(B000000);         // Address pins A5-A0 set to B000000
  driver.setPWMFrequency(50);   // Set frequency to 50Hz

  driver.setChannelPWM(gripCh, pwmGrip.pwmForAngle(gripPos));
  driver.setChannelPWM(wristCh, pwmWrist.pwmForAngle(wristPos));
  driver.setChannelPWM(elbowCh, pwmElbow.pwmForAngle(elbowPos));
}

void loop() {
  // put your main code here, to run repeatedly:
  gripStep(0); //buka
  delay(1000);
  gripStep(-90); //tutup
  delay(1000);


  wristStep(90); //atas
  delay(1000);
  wristStep(30); //bawah
  delay(1000);

  elbowStep(-90); //
  delay(1000);
  elbowStep(180); //
  delay(1000);
}

// SERVO FUNCTIONS
void gripStep(int pos) {
  gripPos = pos;
  if (gripPos < -90) {
    gripPos = -90;
  }
  if (gripPos > 90) {
    gripPos = 90;
  }
  driver.setChannelPWM(gripCh, pwmGrip.pwmForAngle(gripPos));
  //delay(10);
}

void wristStep(int pos) {
  wristPos = pos;
  if (wristPos < -90) {
    wristPos = -90;
  }
  if (wristPos > 90) {
    wristPos = 90;
  }
  driver.setChannelPWM(wristCh, pwmWrist.pwmForAngle(wristPos));
  //delay(10);
}

void elbowStep(int pos) {
  elbowPos = pos;
  if (elbowPos < -90) {
    elbowPos = -90;
  }
  if (elbowPos > 180) {
    elbowPos = 180;
  }
  driver.setChannelPWM(elbowCh, pwmElbow.pwmForAngle(elbowPos));
  //delay(10);
}
