#include "Wire.h" // For I2C
#include <LiquidCrystal_I2C.h> // Added library*
LiquidCrystal_I2C lcd(0x27, 20, 4); // 0x27 is the default I2C bus address of the backpack-see article

#include <Servo.h>
Servo servoPintuMasuk, servoPintuKeluar;

#define Echo_Pintu_Masuk 24
#define Trig_Pintu_Masuk 22
#define Echo_Parkir_B 28
#define Trig_Parkir_B 26
#define Echo_Parkir_C 32
#define Trig_Parkir_C 30
#define Echo_Parkir_D 36
#define Trig_Parkir_D 34
#define Echo_Parkir_E 40
#define Trig_Parkir_E 38
#define Echo_Parkir_F 44
#define Trig_Parkir_F 42
#define Echo_Parkir_G 48
#define Trig_Parkir_G 46
#define Echo_Parkir_H 52
#define Trig_Parkir_H 50
#define Echo_Parkir_I 51
#define Trig_Parkir_I 53
#define Echo_Pintu_Keluar 49
#define Trig_Pintu_Keluar 47

long durasi_1, pintu_masuk;
long durasi_2, jarak_parkiran_B;
long durasi_3, jarak_parkiran_C;
long durasi_4, jarak_parkiran_D;
long durasi_5, jarak_parkiran_E;
long durasi_6, jarak_parkiran_F;
long durasi_7, jarak_parkiran_G;
long durasi_8, jarak_parkiran_H;
long durasi_9, jarak_parkiran_I;
long durasi_10, Pintu_keluar; 
String parkir1, parkir2, parkir3, parkir4, parkir5, parkir6, parkir7, parkir8 = "";
String p1, p2, p3, p4, p5, p6, p7, p8;
int masuk, detect, lastdetect = 0;
String sensor = "";
String terisi = " X    ";
String kosong = " SEDIA";

void setup() {
    Serial.begin(2400);
    pinMode(Echo_Pintu_Masuk, INPUT);
    pinMode(Trig_Pintu_Masuk, OUTPUT);
    pinMode(Echo_Parkir_B, INPUT);
    pinMode(Trig_Parkir_B, OUTPUT);
    pinMode(Echo_Parkir_C, INPUT);
    pinMode(Trig_Parkir_C, OUTPUT);
    pinMode(Echo_Parkir_D, INPUT);
    pinMode(Trig_Parkir_D, OUTPUT);
    pinMode(Echo_Parkir_E, INPUT);
    pinMode(Trig_Parkir_E, OUTPUT);
    pinMode(Echo_Parkir_F, INPUT);
    pinMode(Trig_Parkir_F, OUTPUT);
    pinMode(Echo_Parkir_G, INPUT);
    pinMode(Trig_Parkir_G, OUTPUT);
    pinMode(Echo_Parkir_H, INPUT);
    pinMode(Trig_Parkir_H, OUTPUT);
    pinMode(Echo_Parkir_I, INPUT);
    pinMode(Trig_Parkir_I, OUTPUT);
    pinMode(Echo_Pintu_Keluar, INPUT);
    pinMode(Trig_Pintu_Keluar, OUTPUT);
    servoPintuMasuk.attach(3); 
    servoPintuKeluar.attach(4); 
    servoPintuMasuk.write(90);
    servoPintuKeluar.write(90);
    // Set off LCD module
    lcd.begin(); // 20x4 LCD module
    lcd.backlight();
    lcd.clear(); 
}

void loop(){
    digitalWrite(Trig_Pintu_Masuk, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_Pintu_Masuk, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_Pintu_Masuk, LOW);
    
    durasi_1 = pulseIn(Echo_Pintu_Masuk, HIGH);

    digitalWrite(Trig_Parkir_B, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_Parkir_B, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_Parkir_B, LOW);
    
    durasi_2 = pulseIn(Echo_Parkir_B, HIGH);

    digitalWrite(Trig_Parkir_C, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_Parkir_C, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_Parkir_C, LOW);
    
    durasi_3 = pulseIn(Echo_Parkir_C, HIGH);

    digitalWrite(Trig_Parkir_D, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_Parkir_D, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_Parkir_D, LOW);
    
    durasi_4 = pulseIn(Echo_Parkir_D, HIGH);

    digitalWrite(Trig_Parkir_E, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_Parkir_E, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_Parkir_E, LOW);
    
    durasi_5 = pulseIn(Echo_Parkir_E, HIGH);

    digitalWrite(Trig_Parkir_F, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_Parkir_F, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_Parkir_F, LOW);
    
    durasi_6 = pulseIn(Echo_Parkir_F, HIGH);

    digitalWrite(Trig_Parkir_G, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_Parkir_G, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_Parkir_G, LOW);
    
    durasi_7 = pulseIn(Echo_Parkir_G, HIGH);

    digitalWrite(Trig_Parkir_H, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_Parkir_H, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_Parkir_H, LOW);
    
    durasi_8 = pulseIn(Echo_Parkir_H, HIGH);

    digitalWrite(Trig_Parkir_I, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_Parkir_I, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_Parkir_I, LOW);
    
    durasi_9 = pulseIn(Echo_Parkir_I, HIGH);

    digitalWrite(Trig_Pintu_Keluar, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_Pintu_Keluar, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_Pintu_Keluar, LOW);
    
    durasi_10 = pulseIn(Echo_Pintu_Keluar, HIGH);

    jarak_parkiran_B = durasi_2/58.2;
    if (jarak_parkiran_B<10){
        parkir1 = terisi;
        p1 = "1";}
    else {parkir1 = kosong;
        p1 = "0";}
    jarak_parkiran_C = durasi_3/58.2;
    if (jarak_parkiran_C<10){
        parkir2 = terisi;
        p2 = "1";}
    else {parkir2 = kosong;
        p2 = "0";}
    jarak_parkiran_D = durasi_4/58.2;
    if (jarak_parkiran_D<10){
        parkir3 = terisi;
        p3 = "1";}
    else {parkir3 = kosong;
        p3 = "0";}
    jarak_parkiran_E = durasi_5/58.2;
    if (jarak_parkiran_E<10){
        parkir4 = terisi;
        p4 = "1";}
    else {parkir4 = kosong;
        p4 = "0";}
    jarak_parkiran_F = durasi_6/58.2;
    if (jarak_parkiran_F<10){
        parkir5 = terisi;
        p5 = "1";}
    else {parkir5 = kosong;
        p5 = "0";}
    jarak_parkiran_G = durasi_7/58.2;
    if (jarak_parkiran_G<10){
        parkir6 = terisi;
        p6 = "1";} 
    else {parkir6 = kosong;
        p6 = "0";}
    jarak_parkiran_H = durasi_8/58.2;
    if (jarak_parkiran_H<10){
        parkir7 = terisi;
        p7 = "1";}
    else {parkir7 = kosong;
        p7 = "0";}
    jarak_parkiran_I = durasi_9/58.2;
    if (jarak_parkiran_I<10){
        parkir8 = terisi;
        p8 = "1";}
    else {parkir8 = kosong;
        p8 = "0";}
    
    pintu_masuk = durasi_1/58.2;
    if (pintu_masuk<=10){
        detect = 1;
        servoPintuMasuk.write(0); 
    }
    else {
        detect = 0;
        servoPintuMasuk.write(90); 
    }
    if (detect != lastdetect) {
      if (detect == 1) {
        masuk += 1;
        lastdetect = detect;
      }
      else {
        lastdetect = detect;
      }
    }
    
    Pintu_keluar = durasi_10/58.2;
    if (Pintu_keluar<=10){
        servoPintuKeluar.write(0);
    }
    else {
        servoPintuKeluar.write(90);
    }

  //serialPrint(); //uncomment to troubleshoot sensors

  //Send data to Raspberry Pi
  sensor = String(p1)+String(",")+String(p2)+String(",")+String(p3)+String(",")+String(p4)+String(",")+String(p5)+String(",")+String(p6)+String(",")+String(p7)+String(",")+String(p8);
  Serial.println(sensor);
  
  printLCD();
  delay(1000);
  sensor = "";
}

void printLCD(){
  lcd.setCursor(0,0);
  lcd.print("P1:");
  lcd.setCursor(3,0);
  lcd.print(parkir1);
  lcd.setCursor(0,1);
  lcd.print("P2:");
  lcd.setCursor(3,1);
  lcd.print(parkir2);
  lcd.setCursor(0,2);
  lcd.print("P3:");
  lcd.setCursor(3,2);
  lcd.print(parkir3);
  lcd.setCursor(0,3);
  lcd.print("P4:");
  lcd.setCursor(3,3);
  lcd.print(parkir4);
    
  lcd.setCursor(10,0);
  lcd.print("P5:");
  lcd.setCursor(13,0);
  lcd.print(parkir5);  
  lcd.setCursor(10,1);
  lcd.print("P6:");
  lcd.setCursor(13,1);
  lcd.print(parkir6);
  lcd.setCursor(10,2);
  lcd.print("P7:");
  lcd.setCursor(13,2);
  lcd.print(parkir7);
  lcd.setCursor(10,3);
  lcd.print("P8:");
  lcd.setCursor(13,3);
  lcd.print(parkir8);
}

void serialPrint(){
  Serial.print("jarak Parkiran B: ");
  Serial.println(jarak_parkiran_B);
  Serial.print("jarak Parkiran C: ");
  Serial.println(jarak_parkiran_C);
  Serial.print("jarak Parkiran D: ");
  Serial.println(jarak_parkiran_D);
  Serial.print("jarak Parkiran E: ");
  Serial.println(jarak_parkiran_E);
  Serial.print("jarak Parkiran F: ");
  Serial.println(jarak_parkiran_F);
  Serial.print("jarak Parkiran G: ");
  Serial.println(jarak_parkiran_G);
  Serial.print("jarak Parkiran H: ");
  Serial.println(jarak_parkiran_H);
  Serial.print("jarak Parkiran I: ");
  Serial.println(jarak_parkiran_I);
  Serial.print("masuk: ");
  Serial.println(pintu_masuk);
  Serial.print("keluar: ");
  Serial.println(Pintu_keluar);
}

