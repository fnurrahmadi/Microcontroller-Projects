#include "FreqPeriod.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define lcd2 12
#define buzzer1 8

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial esp(2,3);
double lfrq;
long int pp;
double kph;
String data;

void setup() {
  pinMode(lcd2, OUTPUT);
  digitalWrite(lcd2,HIGH);
  pinMode(buzzer1, OUTPUT);  
  lcd.begin();
  esp.begin(9600);
  Serial.begin(9600);
  FreqPeriod::begin();
  //Serial.println("Memulai Mendeteksi Kecepatan ...");
}

void loop() {
  pp = FreqPeriod::getPeriod();
  if(pp){
    //Serial.print ("period: ");
    //Serial.print(pp);
    //Serial.print(" 1/16us / frequency: ");

    lfrq = 16000400.0 /pp;
    kph = lfrq/19.49;
    //Serial.print(lfrq);
    //Serial.print(" Hz ");
    
    if(kph >= 1.00){
      //Serial.print(kph);
      //Serial.println( " Kph ");
      lcd.clear();
      lcd.setCursor(0, 0);
      //lcd.print(lfrq);
      //lcd.print(" Hz ");
      //lcd.setCursor(0, 1);
      lcd.print(kph);
      lcd.print( " Kph ");
    }

    if(kph >= 10.00){
      //data = String(kph);
      esp.print(String('<')+String(kph)+String('>'));
      delay(50);
      digitalWrite(buzzer1 ,HIGH);
      delay(700);
      digitalWrite(buzzer1, LOW);
    }
  }
}
