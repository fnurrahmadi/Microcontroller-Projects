#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int sensorPin = A0;
int powerPin = 31;

void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH); //dikodingan elu ini low, sensor mati dong?
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("K. Tanah: ");
  int nilaiSensor = analogRead(sensorPin);
  lcd.print(nilaiSensor);
  delay(1000);
}
