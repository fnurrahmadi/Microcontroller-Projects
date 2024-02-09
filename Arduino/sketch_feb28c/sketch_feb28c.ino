#include <Stepper.h>
#include <LiquidCrystal.h>

#define lamp_Channel 7       

int command;            //Int to store app command state.
boolean lamp = false;
boolean gorden = false;

int ForwardPin = 0;
int ReversePin = 0;

// LCD + A = 3.3v and K = GND
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// MOTOR STEPPER
const int StepperMaxRPM = 100;
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 47, 51, 49, 53);

const int ForwardLimitSwitchPin = 23;
const int ReverseLimitSwitchPin = 25;
const int LimitSwitchActivated = HIGH;  // Limit switch grounds pin


void setup() {  
  
      // set up the LCD's number of columns and rows:
      lcd.begin(16, 2);
      pinMode(lamp_Channel, OUTPUT);
      // set the speed at X rpm (motor stepper):
      myStepper.setSpeed(StepperMaxRPM);
      Serial.begin(9600); 

  } 
  
void loop(){
ForwardPin = digitalRead(ForwardLimitSwitchPin);
ForwardPin = LOW;
ReversePin = digitalRead(ReverseLimitSwitchPin);
ReversePin = LOW;  
myStepper.step(0);  
if (Serial.available() > 0) {
  command = Serial.read();  

if (lamp) {
  Serial.println(" RELAY ON");
  lcd.setCursor(0, 1);
  lcd.print(" RELAY ON");
  digitalWrite(lamp_Channel, HIGH);
  myStepper.step(0);}
else {
  Serial.println("RELAY OFF");
  lcd.setCursor(0, 1);
  lcd.print("RELAY OFF");
  digitalWrite(lamp_Channel, LOW);
  myStepper.step(0);}

if (gorden) {
  Serial.println("Gorden Membuka");
  lcd.setCursor(0, 0);
  lcd.print("Gorden Membuka");
  while (digitalRead(ForwardLimitSwitchPin) != LimitSwitchActivated) {
        myStepper.step(1);}
  myStepper.step(0);}
else {
  Serial.println("Gorden Menutup");
  lcd.setCursor(0, 0);
  lcd.print("Gorden Menutup");
  while (digitalRead(ReverseLimitSwitchPin) != LimitSwitchActivated){
        myStepper.step(-1);}
  myStepper.step(0);}
        
switch (command) {
case '1':lamp = true;break;
case 'A':lamp = false;break;
case '2':gorden = true;break;
case 'B':gorden = false;break;
}
}
}
