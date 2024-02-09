#include <Stepper.h>
#include <LiquidCrystal.h>

// Relay pin is controlled with D8. The active wire is connected to Normally Closed and common
int relay = 7;
volatile byte relayState = LOW;

// PIR Motion Sensor is connected to D2.
int PIRInterrupt = 45;
int pirState = LOW;
int val = 0;

// LDR pin is connected to Analog 0
int LDRPin = 43;
// LDR value is stored on LDR reading
int LDRReading;
// LDR Threshold value
int LDRThreshold = 0;

// MOTOR STEPPER
const int StepperMaxRPM = 100;
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 47, 51, 49, 53);

// LIMIT SWITCHES
const int ForwardLimitSwitchPin = 23;
const int ReverseLimitSwitchPin = 25;

// LCD + A = 3.3v and K = GND
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Timer Variables
long lastDebounceTime = 0;  
long debounceDelay = 10000;

void setup() {
  pinMode(PIRInterrupt, INPUT);
  digitalWrite(relay, HIGH);
  Serial.begin(9600);
}
 
void loop(){
  val = digitalRead(PIRInterrupt);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
 
 //   digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
//    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
