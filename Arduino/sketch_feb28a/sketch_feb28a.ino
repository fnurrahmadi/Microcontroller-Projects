#include <Stepper.h>
#include <LiquidCrystal.h>
 
// Relay pin is controlled with D8. The active wire is connected to Normally Closed and common
int relay = 7;
volatile byte relayState = LOW;

// PIR Motion Sensor is connected to D2.
int PIRInterrupt = 45;
int PIRval = 0;
// LDR pin is connected to D3
int LDRPin = 43;
// LDR value is stored on LDR reading
int LDRReading;
// LDR Threshold value
int LDRThreshold = 0;
// led pin
//int ledPin = 13;

// MOTOR STEPPER
const int StepperMaxRPM = 100;
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 47, 51, 49, 53);

// LIMIT SWITCHES
const int ForwardLimitSwitchPin = 23;
const int ReverseLimitSwitchPin = 25;
const int LimitSwitchActivated = HIGH;  // Limit switch grounds pin

// LCD + A = 3.3v and K = GND
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Timer Variables
long lastDebounceTime = 0;  
long debounceDelay = 10000;

void setup() {

  // led pin  
//  pinMode(ledPin, OUTPUT);      // declare LED as output
  
  // Pin for relay module set as output
  pinMode(relay, OUTPUT);
  //digitalWrite(relay, HIGH);
  // PIR motion sensor set as an input
  pinMode(PIRInterrupt, INPUT);
  // Triggers detectMotion function on rising mode to turn the relay on, if the condition is met
  //attachInterrupt(digitalPinToInterrupt(PIRInterrupt), detectMotion, RISING);

  //LIMIT SWITCH
  pinMode(ForwardLimitSwitchPin, INPUT_PULLUP);
  pinMode(ReverseLimitSwitchPin, INPUT_PULLUP);

  // set the speed at X rpm (motor stepper):
  myStepper.setSpeed(StepperMaxRPM);
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
  detectMotion();
  
  // If 10 seconds have passed, the relay is turned off
 /* if((millis() - lastDebounceTime) > debounceDelay && relayState == HIGH){
    digitalWrite(relay, HIGH);
    relayState = LOW;
    //digitalWrite(ledPin, LOW); // turn LED OFF
    //Motor Negative Rotation
    while (digitalRead(ReverseLimitSwitchPin) != LimitSwitchActivated){
      myStepper.step(-1);
    }
    
    Serial.println("Gorden Menutup");
    Serial.println("LED + RELAY OFF");
    // Print a message to the LCD.
    lcd.setCursor(0, 0);
    lcd.print("Gorden Menutup");
    lcd.setCursor(0, 1);
    lcd.print("LED + RELAY OFF");
  }*/
  delay(50);
}

void detectMotion() {
  PIRval = digitalRead(PIRInterrupt);
  if (PIRval == HIGH){
    Serial.println("Motion DETECTED!!!!!!"); //PIR ON
  LDRReading = digitalRead(LDRPin);
  // LDR Reading value is printed on serial monitor, useful to get your LDRThreshold
  Serial.println(LDRReading);
  
    if(LDRReading>=1){
    Serial.println("LDR NO DETECTION");
    Serial.println("Gorden Menutup");
    //lcd
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gorden Menutup");
    lcd.setCursor(0, 1);
    lcd.print("RELAY ON");
    digitalWrite(relay, LOW);
    //digitalWrite(ledPin, LOW);  // turn LED ON
    //Motor Negative Rotation
    while (digitalRead(ReverseLimitSwitchPin) != LimitSwitchActivated){
      myStepper.step(-1);
    }
    
  } else {
    Serial.println("LDR DETECTION");
    Serial.println("Gorden Membuka");
    //lcd
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gorden Membuka");
    lcd.setCursor(0, 1);
    lcd.print("RELAY OFF");
    digitalWrite(relay, HIGH);
    //digitalWrite(ledPin, HIGH); // turn LED OFF
    //Motor Positive Rotation
    while (digitalRead(ForwardLimitSwitchPin) != LimitSwitchActivated) {
      myStepper.step(1);
    }
    
    
  }
  
  } else {
    Serial.println("NO MOTION");
    Serial.println("Gorden Menutup");
    //lcd
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gorden Menutup");
    lcd.setCursor(0, 1);
    lcd.print("RELAY OFF");
    digitalWrite(relay, HIGH);
    //digitalWrite(ledPin, HIGH); // turn LED OFF
    //Motor Positive Rotation
    while (digitalRead(ReverseLimitSwitchPin) != LimitSwitchActivated){
      myStepper.step(-1);
    }
    
  }
    
}
