#include "Wire.h" // For I2C
#include <LiquidCrystal_I2C.h> // Added library*
LiquidCrystal_I2C lcd(0x27, 20, 4); // 0x27 is the default I2C bus address of the backpack-see article

#define Echo_Parkir_B 28
#define Trig_Parkir_B 26
#define Echo_Parkir_C 32
#define Trig_Parkir_C 30
#define Echo_Parkir_D 36
#define Trig_Parkir_D 34

long durasi_2, jarak_parkiran_B;
long durasi_3, jarak_parkiran_C;
long durasi_4, jarak_parkiran_D;

String parkir1, parkir2, parkir3;
char p1, p2, p3 = '0';
char p4 = '1';
char p5 = '0';
char p6 = '0';
char p7 = '1';
char p8 = '0';
String sensor;
String terisi = " X    ";
String kosong = " SEDIA";

//int menghitung = 0;
//int freeslot = 0;

void setup() {
    Serial.begin(9600);
    pinMode(Echo_Parkir_B, INPUT);
    pinMode(Trig_Parkir_B, OUTPUT);
    pinMode(Echo_Parkir_C, INPUT);
    pinMode(Trig_Parkir_C, OUTPUT);
    pinMode(Echo_Parkir_D, INPUT);
    pinMode(Trig_Parkir_D, OUTPUT);

    // Set off LCD module
    lcd.begin(); // 20x4 LCD module
    lcd.backlight();
    lcd.clear(); 
}

void loop(){
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

    jarak_parkiran_B = durasi_2/58.2;
    if (jarak_parkiran_B<6){
        parkir1 = terisi;
        p1 = '1';}
    else {parkir1 = kosong;
        p1 = '0';}
    jarak_parkiran_C = durasi_3/58.2;
    if (jarak_parkiran_C<6){
        parkir2 = terisi;
        p2 = '1';}
    else {parkir2 = kosong;
        p2 = '0';}
    jarak_parkiran_D = durasi_4/58.2;
    if (jarak_parkiran_D<6){
        parkir3 = terisi;
        p3 = '1';}
    else {parkir3 = kosong;
        p3 = '0';}
      
  //menghitung = parkir1 + parkir2 + parkir3 + parkir4 + parkir5 + parkir6 + parkir7 + parkir8;
  //freeslot = 8 - menghitung;
  //Serial.println(freeslot);
  //serialPrint();

  //Send data to Raspberry Pi
  sensor = String(p1)+String(",")+String(p2)+String(",")+String(p3)+String(",")+String(p4)+String(",")+String(p5)+String(",")+String(p6)+String(",")+String(p7)+String(",")+String(p8);
  Serial.print(sensor);
  
  printLCD();
  delay(1000);
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
}

void serialPrint(){
  Serial.print("jarak Parkiran B: ");
  Serial.println(jarak_parkiran_B);
  Serial.print("jarak Parkiran C: ");
  Serial.println(jarak_parkiran_C);
  Serial.print("jarak Parkiran D: ");
  Serial.println(jarak_parkiran_D);
  Serial.println("");
}

