/*
   SMART ROOM WITH SINGLE CURTAIN AND SINGLE LAMP FUNCTIONS USING AN
   LDR SENSOR FOR LIGHT DETECTION TO DIFFER NIGHT AND DAY
   AND A PIR SENSOR TO DETECT HUMAN PRESENCE IN THE ROOM
   ANDROID APP CREATED USING MITAPPINVENTOR2 WITH BLUETOOTH FUNCTION

   THIS IS A PROJECT WHOSE CONTRIBUTORS ARE FROM
   UNIVERSITY OF GUNADARMA
   FACULTY OF COMPUTER SCIENCE AND INFORMATION TECHNOLOGY
   MAJOR OF COMPUTER SYSTEM
   FAKHRI NURRAHMADI
   AND
   IKBAL RULLAH
*/

// LIBRARIES NEEDED
#include <Stepper.h>
#include <LiquidCrystal.h>

// BLUETOOTH APP VARIABLES
int Command;                    // INT TO STORE APP COMMAND STATE.
boolean Lamp = false;
boolean Curtain = false;

// RELAY PIN D53. ACTIVE WIRED CONNECTED TO NORMALLY OPEN AND COMMON
int RelayPin = 53;

// PIR SENSOR ON D13
int PIRPin = 13;
int PIRVal = 0;

/*
   THE LDR WE USED IS A DIGITAL MODULE WITH DIGITAL DATA
   0 WHEN DETECTING LIGHT, AND 1 WHEN DETECTING NO LIGHT
   USING AN LDR WITH ANALOG DATA WOULD MEAN THAT THE CODE HAS TO ADAPT
   BY USING AN ANALOG PIN, CHANGING THE THRESHOLD VALUE BY EXPERIMENTING,
   AND USING AN ANALOGREAD FUNCTION INSTEAD OF DIGITALREAD
   USE THE SERIAL MONITOR TO CHECK THE ANALOG DATA OF THE LDR
*/

// LDR SENSOR ON D12
int LDRPin = 10;
// LDR VALUE FROM DIGITALREAD
int LDRReading;
// VALUE TO COMPARE A DIGITAL LDR INPUT
int LDRThreshold = 0;

// MOTOR STEPPER
const int StepperMaxRPM = 100;
const int StepsPerRevolution = 200;
// INITIALIZE STEPPER LIBRARY ON PINS 47, 51, 49, 53
// THE PINS ARE AS SUCH DUE TO THE WAY WE CONNECTED THE STEPPER WIRES
Stepper CurtainStepper(StepsPerRevolution, 40, 42, 41, 43);

// LIMIT SWITCHES D11 AND D12
const int ForwardLimitSwitchPin = 11;
const int ReverseLimitSwitchPin = 12;
const int LimitSwitchActivated = HIGH;
int ForwardPin = 0;
int ReversePin = 0;

// LCD PINS
// TO HAVE BACKLIGHT, A = 3.3/5V, K = GND
const int rs = 39, en = 37, d4 = 35, d5 = 33, d6 = 31, d7 = 29;
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);

void setup() {

  // RELAY
  pinMode(RelayPin, OUTPUT);
  digitalWrite(RelayPin, HIGH);

  // PIR SENSOR
  pinMode(PIRPin, INPUT);
  // THE PREVIOUS VERSION OF THE PIR INPUT ACTS ON RISING EDGE ONLY
  // attachInterrupt(digitalPinToInterrupt(PIRPin), detectMotion, RISING);

  // LIMIT SWITCH
  pinMode(ForwardLimitSwitchPin, INPUT_PULLUP);
  pinMode(ReverseLimitSwitchPin, INPUT_PULLUP);

  // SPEED OF THE STEPPER
  CurtainStepper.setSpeed(StepperMaxRPM);
  Serial.begin(9600);

  // LCD NUMBER OF COLUMNS AND ROWS
  LCD.begin(16, 2);
}

// FUNCTION FOR AUTOMATIC MODE
void AutomaticMode() {

  // READS PIR SENSOR INPUT
  PIRVal = digitalRead(PIRPin);

  // CONDITION FOR WHEN PIR DETECTS HUMAN PRESENCE
  if (PIRVal == HIGH) {
    Serial.println("Motion DETECTED!!!!!!");

    // READS LDR SENSOR INPUT
    LDRReading = digitalRead(LDRPin);
    Serial.println(LDRReading);

    // CONDITION FOR WHEN PIR DETECTS AND LDR DOES NOT
    if (LDRReading >= 1) {

      Serial.println("LDR NO DETECTION");
      Serial.println("Gorden Menutup");
      Serial.println("RELAY ON ");
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("Gorden Menutup");
      LCD.setCursor(0, 1);
      LCD.print("RELAY ON ");
      digitalWrite(RelayPin, HIGH);    // LAMP TURNS ON
      // STEPPER COUNTER CLOCKWISE ROTATION UNTIL REVERSE SWITCH IS PRESSED
      while (digitalRead(ReverseLimitSwitchPin) != LimitSwitchActivated) {
        CurtainStepper.step(-1);
      }
      //LDRReading = digitalRead(LDRPin);

    }

    // CONDITION FOR WHEN PIR DETECTS AND LDR DETECTS
    else {

      Serial.println("LDR DETECTION");
      Serial.println("Gorden Membuka");
      Serial.println("RELAY OFF");
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("Gorden Membuka");
      LCD.setCursor(0, 1);
      LCD.print("RELAY OFF");
      digitalWrite(RelayPin, LOW);   // LAMP TURNS OFF
      // STEPPER CLOCKWISE ROTATION UNTIL FORWARD SWITCH IS PRESSED
      while (digitalRead(ForwardLimitSwitchPin) != LimitSwitchActivated) {
        CurtainStepper.step(1);
      }
      // LDRReading = digitalRead(LDRPin);
    }

  }

  // CONDITION FOR WHEN PIR DOES NOT DETECT, LDR DISREGARDED
  else {
    Serial.println("NO MOTION");
    Serial.println("Gorden Menutup");
    Serial.println("RELAY OFF");
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Gorden Menutup");
    LCD.setCursor(0, 1);
    LCD.print("RELAY OFF");
    digitalWrite(RelayPin, LOW);   // LAMP TURNS OFF
    //STEPPER COUNTER CLOCKWISE ROTATION UNTIL REVERSE SWITCH IS PRESSED
    while (digitalRead(ReverseLimitSwitchPin) != LimitSwitchActivated) {
      CurtainStepper.step(-1);
    }
    //LDRReading = digitalRead(LDRPin);
  }

}

/*
   BEFORE TRYING TO CONNECT THE BLUETOOTH FROM THE ANDROID APP
   PLEASE PAIR THE DEVICES BEFOREHAND TO ENSURE SUCCESSFUL CONNECTION
*/

// LOOP DECIDES AUTOMATIC MODE OR MANUAL MODE FROM BLUETOOTH DETECTION
void loop() {

  // AUTOMATIC MODE WHEN BLUETOOTH CONNECTION IS NOT DETECTED
  if (Serial.available() <= 0) {
    AutomaticMode();
  }

  // MANUAL MODE FROM ANDROID APP WHEN BLUETOOTH CONNECTION IS DETECTED
  else if (Serial.available() > 0) {

    // JUST MY COUNTERMEASURES TO RESET THE SWITCH INPUT AND STEPPER STATE
    ForwardPin = digitalRead(ForwardLimitSwitchPin);
    ForwardPin = LOW;
    ReversePin = digitalRead(ReverseLimitSwitchPin);
    ReversePin = LOW;
    CurtainStepper.step(0);

    // STORES INPUT FROM APP BUTTONS
    Command = Serial.read();

    // TO TURN LAMP ON
    if (Command == '1') {
      Serial.println("RELAY ON ");
      LCD.setCursor(0, 1);
      LCD.print("RELAY ON ");
      digitalWrite(RelayPin, HIGH);
    }
    // TO TURN LAMP OFF
    else if (Command == 'A') {
      Serial.println("RELAY OFF");
      LCD.setCursor(0, 1);
      LCD.print("RELAY OFF");
      digitalWrite(RelayPin, LOW);
    }
    // TO OPEN THE CURTAIN
    else if (Command == '2') {
      Serial.println("Gorden Membuka");
      LCD.setCursor(0, 0);
      LCD.print("Gorden Membuka");
      while (digitalRead(ForwardLimitSwitchPin) != LimitSwitchActivated) {
        CurtainStepper.step(1);
      }
      CurtainStepper.step(0);
    }
    // TO CLOSE THE CURTAIN
    else if (Command == 'B') {
      Serial.println("Gorden Menutup");
      LCD.setCursor(0, 0);
      LCD.print("Gorden Menutup");
      while (digitalRead(ReverseLimitSwitchPin) != LimitSwitchActivated) {
        CurtainStepper.step(-1);
      }
      CurtainStepper.step(0);
    }

  }
  delay(50);

}
