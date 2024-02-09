#define lamp_Channel 7   		

int command; 			      //Int to store app command state.
boolean lamp = false;

void setup() {  
   	  pinMode(lamp_Channel, OUTPUT);
      Serial.begin(9600); 
  } 
  
void loop(){
  
if (Serial.available() > 0) {
	command = Serial.read();
	

if (lamp) {digitalWrite(lamp_Channel, HIGH);}
else {digitalWrite(lamp_Channel, LOW);}

switch (command) {

case 'L':lamp = true;break;
case 'l':lamp = false;break;
}
}
}
