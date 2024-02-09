#include <Stepper.h>

int PIRInterrupt = 2;

const int stepsPerRevolution = 200;
const int ForwardLimitSwitchPin = 23;
const int ReverseLimitSwitchPin = 25;
const int LimitSwitchActivated = HIGH;  // Limit switch grounds pin
const int StepperMaxRPM = 100;

Stepper stepper(stepsPerRevolution, 47, 51, 49, 53);

void setup() {
   pinMode(ForwardLimitSwitchPin, INPUT_PULLUP);
   pinMode(ReverseLimitSwitchPin, INPUT_PULLUP);
   stepper.setSpeed(StepperMaxRPM);
   pinMode(PIRInterrupt, INPUT);
  // Triggers detectMotion function on rising mode to turn the relay on, if the condition is met
  attachInterrupt(digitalPinToInterrupt(PIRInterrupt), detectMotion, RISING);
  
}

void loop() {
   // Step forward until the limit switch is activated
   while (digitalRead(ForwardLimitSwitchPin) != LimitSwitchActivated) {
       stepper.step(1);
   }
   // Step reverse until the limit switch is activated
   while (digitalRead(ReverseLimitSwitchPin) != LimitSwitchActivated) {
       stepper.step(-1);
   }
}

void detectMotion()  {
  stepper.step(1);
}

