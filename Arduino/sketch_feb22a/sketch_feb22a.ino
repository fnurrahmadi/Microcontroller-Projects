#include <Stepper.h>


/*LDR SENSOR*/
int LDRPin = 3; // select the input pin for LDR 
int LDRValue = 0; // variable to store the value coming from the sensor 

/*PIR SENSOR*/
int ledPin = 13;                // choose the pin for the LED
int PIRPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int PIRval = 0;                    // variable for reading the pin status

/*RELAY*/
int relayInput = 7;

void setup() {  
pinMode(ledPin, OUTPUT);      // declare LED as output
pinMode(PIRPin, INPUT);     // declare sensor as input
 
pinMode(PIRPin, INPUT);
pinMode(relayInput, OUTPUT); 

Serial.begin(9600); //sets serial port for communication
} 

/*LDR Light Detector*/
void ldrloop() { 
LDRValue = digitalRead(LDRPin); // read the value from the sensor 
Serial.println(LDRValue); //prints the values coming from the sensor on the screen 
delay(100); 
}

/*PIR Motion Detector*/
void pirloop(){
  PIRval = digitalRead(PIRPin);  // read input value
  if (PIRval == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, LOW);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else { 
      
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}

/*Relay + PIR Motion*/
void relayloop() {
  int sensorValue = digitalRead(PIRPin);
  if (sensorValue == 1) {
    digitalWrite(relayInput, LOW); // The Relay Input works Inversly
  }
}
