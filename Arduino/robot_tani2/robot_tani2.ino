//------------------------LIBRARIES-------------------------
// E0:75:0A:90:98:76

#include <Servo.h>
#include "A4988.h"
#include "SyncDriver.h"
#include <BTS7960.h>

//---------------------------PINS---------------------------

#define R_PWM_KIRI 11
#define R_EN_KIRI 13
#define L_PWM_KIRI 10
#define L_EN_KIRI 12

#define R_PWM_KANAN 6
#define R_EN_KANAN 8
#define L_PWM_KANAN 5
#define L_EN_KANAN 7

#define pneumaticValve 48
#define relayCutter 49

#define gripperPin 44  // 180 kunci, 0 buka
#define wristPin 45  //90 normal
#define cutterPin 46 // 50 potong, 180 buka

#define DIRX 31 // dituker gamau jadi pesawat 
#define STEPX 29 // dituker gamau jadi pesawat
#define MS1X 23 // dituker gamau jadi pesawat
#define MS2X 25 // dituker gamau jadi pesawat
#define MS3X 27 // dituker gamau jadi pesawat
#define ENX 33 // dituker gamau jadi pesawat

#define DIRY 30 // dituker gamau jadi pesawat
#define STEPY 28 // dituker gamau jadi pesawat
#define MS1Y 22 // dituker gamau jadi pesawat
#define MS2Y 24 // dituker gamau jadi pesawat
#define MS3Y 26 // dituker gamau jadi pesawat
#define ENY 32 // dituker gamau jadi pesawat

//------------------------VARIABLES-------------------------

int stepperSteps = 200;
int stepperRPM = 300;
int stepperCM = -220; // ~0,5 CENTIMETER

int x = 0; // save koordinat sebelum
int y = 0; // save koordinat sebelum

int taX = 15;
int taY = 7;

int gripPosition = 0; // posisi buka
int wristPosition = 90; // posisi buka
int cutterPosition = 180; // posisi buka
int cutterCut = 30 ; // posisi potong

int motorSpeedKiri = -120; //(0-127 cw, 128-255 ccw)
int motorSpeedKanan = 124;

byte joystickData;

bool pneuCondition = false;
bool relaycutterCondition = true;
int counterTanam = 1;
int gripped = 0;

int prosesTanam = 0;

A4988 stepperX(stepperSteps, DIRX, STEPX, MS1X, MS2X, MS3X);
A4988 stepperY(stepperSteps, DIRY, STEPY, MS1Y, MS2Y, MS3Y);
SyncDriver controller(stepperX, stepperY);
Servo gripper;
Servo wrist;
Servo cutter;
BTS7960 motorKiri(R_PWM_KIRI, L_PWM_KIRI, L_EN_KIRI, R_EN_KIRI);
BTS7960 motorKanan(R_PWM_KANAN, L_PWM_KANAN, L_EN_KANAN, R_EN_KANAN);

//-------------------------SETUP----------------------------

void setup() {
  pinMode(pneumaticValve, OUTPUT);
  pinMode(relayCutter, OUTPUT);

  gripper.attach(gripperPin);
  gripper.write(gripPosition);
  wrist.attach(wristPin);
  wrist.write(wristPosition);
  cutter.attach(cutterPin);
  cutter.write(cutterPosition);

  stepperX.begin(stepperRPM, 1);
  stepperY.begin(stepperRPM, 1);
  stepperX.setEnableActiveState(LOW);
  stepperY.setEnableActiveState(LOW);

  digitalWrite(relayCutter, HIGH);

  Serial.begin(2400);

  motorKiri.enable();
  motorKanan.enable();
  
  // cartesian(15,0);
  // pneumaticToggle();
  // delay(5000);
  // pneumaticToggle();
  
  // cartesian(15,13);
  // pneumaticToggle();
  // delay(5000);
  // pneumaticToggle();
  
  
  // cartesian(29,0);
  // pneumaticToggle();
  // delay(5000);
  // pneumaticToggle();
  
  // cartesian(29,7); 
  // pneumaticToggle();
  // delay(5000);
  // pneumaticToggle();
  
  // cartesian(29,13);
  // pneumaticToggle();
  // delay(5000);
  // pneumaticToggle();

//----------------------------------------------------------

  gripper.write(gripPosition);
  wrist.write(wristPosition);
  cutter.write(cutterPosition);
}

//--------------------------LOOP----------------------------

void loop() {
  if (Serial.available()) {
    joystickData = Serial.read();
    Serial.println(joystickData);
    joystickOptions();
    // Serial.flush();
  }
}

//------------------------JOYSTICK---------------------------

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

  else if (joystickData == 'A') {
    // MANUAL RELAY CUTTER TOGGLE
    relayCutterToggle();
  }
  else if (joystickData == 'B') {
    // MANUAL GRIP TOGGLE
    if (gripped == 0) {
      gripToggle(180);
      gripped = 1;
    }
    else if (gripped == 1) {
      gripToggle(0);
      gripped = 0;
    }
  }
  else if (joystickData == 'C') {
    // MANUAL PNEUMATIC TOGGLE
    pneumaticToggle();
  }
  else if (joystickData == 'D') {
    // HANDBREAK
    roam(0, 0);
    //software_Reset();
  }

  // CONSOLE BUTTONS (TRIANGLE, O, X, SQUARE)
  else if (joystickData == 'E') {
    prosesTanam = 1;
  }

  if (prosesTanam == 1) {
    // AUTO TANAM
    if (counterTanam == 1) {
      // cartesian(taX, taY);
      // pneumaticToggle(); //DROP PNEUMATIC
      // gripToggle(0); //masukan pos buka
      // pneumaticToggle(); //LIFT PNEUMATIC
      // cartesian(1, taY);

      cartesian(taX, taY);
      pneumaticToggle(); //DROP PNEUMATIC
      counterTanam = 2;
      prosesTanam = 0;
    }
    else if (counterTanam == 2) {
      // gripToggle(180); //masukan pos tutup
      // cartesian(taX, taY);
      // pneumaticToggle(); //DROP PNEUMATIC
      // gripToggle(0); //masukan pos buka
      // pneumaticToggle(); //LIFT PNEUMATIC
      // cartesian(13, taY);
      // cartesian(13, 20);
      // counterTanam = 3;
      cartesian(1, taY);
      cartesian(1, 20);
      gripToggle(180); //masukan pos tutup
      delay(1000);
      cartesian(taX, taY);
      pneumaticToggle(); //DROP PNEUMATIC
      counterTanam = 3 ;
      prosesTanam = 0;
    }
    else if (counterTanam == 3) {
      // gripToggle(180); //masukan pos tutup
      // cartesian(taX, taY);
      // pneumaticToggle(); //DROP PNEUMATIC
      // gripToggle(0); //masukan pos buka
      // pneumaticToggle(); //LIFT PNEUMATIC
      cartesian(13, taY);
      cartesian(13, 20);
      gripToggle(180); //masukan pos tutup
      delay(1000);
      cartesian(taX, taY);
      pneumaticToggle(); //DROP PNEUMATIC
      prosesTanam = 0;
    }
  }

  // LEFT ANALOG PRESS - L3
  else if (joystickData == 'F') {
    // RESET CNC POSITION
    cartesian(0, 0);
  }

  // SELECT BUTTON
  else if (joystickData == 'G') {
    // AUTO SEMAI-CABUT RUMPUT
    // gripToggle(0); //masukan pos buka
    // cartesian(taX, taY);
    // pneumaticToggle(); //DROP PNEUMATIC
    // delay(1000);
    // gripToggle(180); //masukan pos tutup
    // wristToggle(180); // masukan pos putar
    // gripToggle(0); //masukan pos buka
    // wristToggle(90); // masukan pos putar ke posisi normal
    cartesian(taX, 34);
  }

  // START BUTTON
  else if (joystickData == 'H') {
    //AUTO PANEN
    gripToggle(0); //masukan pos buka
    delay(1000);
    cartesian(18, taY); // koordinat panen
    cartesian(18, 34); // koordinat panen
    gripToggle(180); // grip tutup
    delay(1000);
    // relayCutterToggle();
    // cutterToggle(cutterCut); //masukan pos memotong
    // cutterToggle(cutterPosition); //masukan pos kembali ke posisi normal
    // relayCutterToggle();
    // wristToggle(150); // masukan pos putar ke posisi miring
  }

  // CNC - R2 DPAD
  else if (joystickData == 'I') {
    //UP;
    cartesian(x, y+1);
  }
  else if (joystickData == 'J') {
    //DOWN
    cartesian(x, y-1);
  }
  else if (joystickData == 'K') {
    //RIGHT
    cartesian(x+1, y);
  }
  else if (joystickData == 'L') {
    //LEFT
    cartesian(x-1, y);
  }

  // SHOULDER BUTTONS
  else if (joystickData == 'M') {
    // MANUAL TOGGLE CUTTER SERVO CUT
    cutterStep(-20);
  }
  else if (joystickData == 'N') {
    // MANUAL TOGGLE CUTTER SERVO OPEN
    cutterStep(20);
  }
  // SERVO WRIST - LEFT ANALOG
  else if (joystickData == 'O') {
    wristStep(-20); //CCW
  }
  else if (joystickData == 'P') {
    wristStep(20); //CW
  }

  else if (joystickData == 'T') {
    // TOGGLE PLUS COUNTER TANAM
    counterTanam--;
    if (counterTanam < 1) {
      counterTanam = 1;
    }
  }
  else if (joystickData == 'R') {
    // TOGGLE MINUS COUNTER TANAM
    counterTanam++;
    if (counterTanam > 3) {
      counterTanam = 3;
    }
  }

  else if (joystickData == 'Z') {
  }
}

//------------------------FUNCTIONS------------------------

// MOVEMENT FUNCTION
void roam(int pwmkiri, int pwmkanan) {
  motorKiri.setSpeed(pwmkiri);
  motorKanan.setSpeed(pwmkanan);
}

// SERVO FUNCTIONS
void cutterStep(int pos) {
  cutterPosition += pos;
  cutter.write(cutterPosition);
  if(cutterPosition < 0){
    cutterPosition = 0;
  }
  else if(cutterPosition > 180){
    cutterPosition = 180;
  }
  //delay(10);  
}
void cutterToggle(int pos) {
  //  cutterPosition += pos;
  cutter.write(pos);
  //delay(10);
}
void wristToggle(int pos) {
  //wristPosition += pos;
  wrist.write(pos);
  //delay(10);
}
void wristStep(int pos) {
  wristPosition += pos;
  wrist.write(wristPosition);
  if(wristPosition < 0){
    wristPosition = 0;
  }
  else if(wristPosition > 180){
    wristPosition = 180;
  }
  //delay(10);
}
void gripToggle(int pos) {
  //gripPosition += pos;
  gripper.write(pos);
  //delay(10);
}

// RELAY CUTTER
void relayCutterToggle() {
  if (relaycutterCondition == false) {
    digitalWrite(relayCutter, HIGH);
    relaycutterCondition = true;
  }
  else if (relaycutterCondition == true) {
    digitalWrite(relayCutter, LOW);
    relaycutterCondition = false;
  }
}

// PNEUMATIC RELAY FUNCTION
void pneumaticToggle() {
  if ( pneuCondition == false ) {
    digitalWrite(pneumaticValve, HIGH);
    pneuCondition = true;
  }
  else if ( pneuCondition == true ) {
    digitalWrite(pneumaticValve, LOW);
    pneuCondition = false;
  }
}

// CARTESIAN FUNCTIONS
void cartesian(int X1, int Y1) {
  int deltaX = X1 - x;
  int deltaY = Y1 - y;
  controller.rotate(deltaX * stepperCM , deltaY * stepperCM);
  x = X1;
  y = Y1;
}

// SOFTWARE RESET
void software_Reset(){
  asm volatile ("  jmp 0");
}
