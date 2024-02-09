/* Arduino tutorial - Buzzer / Piezo Speaker
   More info and circuit: http://www.ardumotive.com/how-to-use-a-buzzer-en.html
   Dev: Michalis Vasilakis // Date: 9/6/2015 // www.ardumotive.com */

const int buzzer = 42; //buzzer to arduino pin 42

void setup(){
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
}

//c a a# a g f a c f
void loop(){
  //tone(buzzer, 1000);
  
  tone(buzzer, 523.25);  //c
  delay(250);
  tone(buzzer, 440);      //a
  delay(250);
  tone(buzzer, 466.16);   //a#
  delay(125);
  tone(buzzer, 440);      //a
  delay(125);
  tone(buzzer, 392);   //g
  delay(250);
  tone(buzzer, 349.23);   //f
  delay(250);
  tone(buzzer, 440);      //a
  delay(250);
  tone(buzzer, 523.25);  //c
  delay(250);
  tone(buzzer, 349.23);   //f
  delay(500);    
  noTone(buzzer);     
  delay(2000);
     
}
