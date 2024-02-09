#include<Servo.h>
Servo servoku;

int PotPin = A0;
int nilai;

void setup()
{
  servoku.attach(3);
}

void loop()
{
  nilai = analogRead(PotPin);
  nilai = map(nilai, 0, 1023, 0, 180);
  servoku.write(nilai);
  delay(15);
}

