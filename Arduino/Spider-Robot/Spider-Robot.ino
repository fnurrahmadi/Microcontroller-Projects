#include <DynamixelSerial.h>
#include <SoftwareSerial.h>
//
DynamixelSerial Dynamixel;
int x=200;
int pelan=80;

void setup(){
SoftwareSerial BT(11,12);
Dynamixel.begin(1000000,3,4,2);  // Inicialize the servo at 1Mbps and Pin Control 2
Serial.begin(9600);
BT.begin (9600);
jongkok();

}

void berdiri(){
  //siap mode 2
 //berdiri
 Dynamixel.moveSpeed(1, 400,x);
 delay(50);
 Dynamixel.moveSpeed(8, 500,x);
  delay(50);
 Dynamixel.moveSpeed(13,650,x);
  delay(50);
  Dynamixel.moveSpeed(14, 400,x);
   delay(50);
 Dynamixel.moveSpeed(2,600,x);
  delay(50);
 Dynamixel.moveSpeed(7, 550,x);
  delay(250);
   Dynamixel.moveSpeed(5,600,x);
   delay(50);
  Dynamixel.moveSpeed(12,600,x);
   delay(50);
  Dynamixel.moveSpeed(17,400,x);
   delay(50); 
    Dynamixel.moveSpeed(18,600,x);
     delay(50);
  Dynamixel.moveSpeed(6,400,x);
   delay(50);
  Dynamixel.moveSpeed(11,400,x);
  Dynamixel.moveSpeed(10,600,x);
   delay(50);
  Dynamixel.moveSpeed(3,600,x);
   delay(50);
  Dynamixel.moveSpeed(15,400,x);
   delay(50);
    Dynamixel.moveSpeed(16,600,x);
     delay(50);
  Dynamixel.moveSpeed(4,400,x);
   delay(50);
  Dynamixel.moveSpeed(9,400,x);
  delay(250);
}

void jongkok()
{
  //siap
 Dynamixel.moveSpeed(1,300,x);
 Dynamixel.moveSpeed(8,500,x);
 Dynamixel.moveSpeed(13,650,x);
 Dynamixel.moveSpeed(14,400,x);
 Dynamixel.moveSpeed(2,700,x);
    Dynamixel.moveSpeed(7, 500,x);
  delay(250);
  Dynamixel.moveSpeed(3,300,x);
  Dynamixel.moveSpeed(10,300,x);
  Dynamixel.moveSpeed(15,700,x);
  Dynamixel.moveSpeed(16,300,x);
    Dynamixel.moveSpeed(4,700,x);
     Dynamixel.moveSpeed(9,700,x);
  delay(250);
  Dynamixel.moveSpeed(5,330,x);
  Dynamixel.moveSpeed(12,300,x);
  Dynamixel.moveSpeed(17,700,x);
    Dynamixel.moveSpeed(18,300,x);
      Dynamixel.moveSpeed(6,700,x);
        Dynamixel.moveSpeed(11,700,x);
}

void depan_kiri() {
  Dynamixel.moveSpeed(4,800,x);
  Dynamixel.moveSpeed(2,500,x);
  delay(300);
  Dynamixel.moveSpeed(4,700,x);
  delay(300);
  Dynamixel.moveSpeed(2,700,pelan);
}

void depan_kanan() {
  Dynamixel.moveSpeed(3,200,x);
  Dynamixel.moveSpeed(1,500,x);
  delay(500);
  Dynamixel.moveSpeed(3,300,x);
  delay(500);
  Dynamixel.moveSpeed(1,300,pelan);
}

void samping_kiri() {
  Dynamixel.moveSpeed(10,200,x);
  Dynamixel.moveSpeed(8,300,x);
  delay(500);
  Dynamixel.moveSpeed(10,300,x);
  delay(500);
  Dynamixel.moveSpeed(8,500,pelan);
}

void samping_kanan() {
  Dynamixel.moveSpeed(9,800,x);
  Dynamixel.moveSpeed(7,650,x);
  delay(500);
  Dynamixel.moveSpeed(9,700,x);
  delay(500);
  Dynamixel.moveSpeed(7,500,pelan);
}

void belakang_kiri() {
  Dynamixel.moveSpeed(16,200,x);
  Dynamixel.moveSpeed(14,200,x);
  delay(500);
  Dynamixel.moveSpeed(16,300,x);
  delay(500);
  Dynamixel.moveSpeed(14,400,pelan);
}


void belakang_kanan() {
  Dynamixel.moveSpeed(15,800,x);
  Dynamixel.moveSpeed(13,750,x);
  delay(500);
  Dynamixel.moveSpeed(15,700,x);
  delay(500);
  Dynamixel.moveSpeed(13,650,pelan);
}

void maju3kaki_1() {
  Dynamixel.moveSpeed(4,800,x);
  Dynamixel.moveSpeed(2,500,x);
  Dynamixel.moveSpeed(9,800,x);
  Dynamixel.moveSpeed(7,700,x);
    Dynamixel.moveSpeed(16,200,x);
  Dynamixel.moveSpeed(14,200,x);
  delay(500);
  Dynamixel.moveSpeed(4,700,x);
   Dynamixel.moveSpeed(9,700,x);
   Dynamixel.moveSpeed(16,300,x);
   delay(500);
   Dynamixel.moveSpeed(2,700,pelan);
   Dynamixel.moveSpeed(7,500,pelan);
   Dynamixel.moveSpeed(14,400,pelan);
    }


void maju3kaki_2(){
  Dynamixel.moveSpeed(3,200,x);
  Dynamixel.moveSpeed(1,500,x);
    Dynamixel.moveSpeed(10,200,x);
  Dynamixel.moveSpeed(8,300,x);
        Dynamixel.moveSpeed(15,800,x);
  Dynamixel.moveSpeed(13,850,x);
  delay(500);
    Dynamixel.moveSpeed(10,300,x);
  Dynamixel.moveSpeed(3,300,x);
    Dynamixel.moveSpeed(15,700,x);
  delay(500);
  Dynamixel.moveSpeed(1,300,pelan);
    Dynamixel.moveSpeed(8,500,pelan);
      Dynamixel.moveSpeed(13,650,pelan);
}

     void mundur3kaki_1() {
  Dynamixel.moveSpeed(16,200,x);
  Dynamixel.moveSpeed(14,500,x);
  Dynamixel.moveSpeed(9,800,x);
  Dynamixel.moveSpeed(7,300,x);
    Dynamixel.moveSpeed(4,800,x);
  Dynamixel.moveSpeed(2,800,x);
  delay(500);
  Dynamixel.moveSpeed(16,300,x);
   Dynamixel.moveSpeed(9,700,x);
   Dynamixel.moveSpeed(4,700,x);
   delay(500);
  Dynamixel.moveSpeed(14,300,pelan); 
   Dynamixel.moveSpeed(7,400,pelan);
   Dynamixel.moveSpeed(2,600,pelan);
     }
     
   void mundur3kaki_2(){
  Dynamixel.moveSpeed(15,800,x);
  Dynamixel.moveSpeed(13,550,x);
    Dynamixel.moveSpeed(10,200,x);
  Dynamixel.moveSpeed(8,700,x);
        Dynamixel.moveSpeed(3,200,x);
  Dynamixel.moveSpeed(1,200,x);
  delay(500);
   Dynamixel.moveSpeed(15,700,x); 
  Dynamixel.moveSpeed(3,300,x);
    Dynamixel.moveSpeed(10,300,x);
  delay(500);
  Dynamixel.moveSpeed(13,750,pelan);
    Dynamixel.moveSpeed(8,500,pelan);
      Dynamixel.moveSpeed(1,400,pelan);
        }

void belok3kaki_1(){
Dynamixel.moveSpeed(3,200,x);
  Dynamixel.moveSpeed(1,650,x);
    Dynamixel.moveSpeed(10,200,x);
  Dynamixel.moveSpeed(8,700,x);
        Dynamixel.moveSpeed(15,800,x);
  Dynamixel.moveSpeed(13,850,x);
  delay(500);
    Dynamixel.moveSpeed(10,300,x);
  Dynamixel.moveSpeed(3,300,x);
    Dynamixel.moveSpeed(15,700,x);
  delay(500);
  Dynamixel.moveSpeed(1,200,pelan);
    Dynamixel.moveSpeed(8,500,pelan);
      Dynamixel.moveSpeed(13,650,pelan);
}

void belok3kaki_2(){
       Dynamixel.moveSpeed(4,800,x);
  Dynamixel.moveSpeed(2,900,x);
  Dynamixel.moveSpeed(9,800,x);
  Dynamixel.moveSpeed(7,700,x);
    Dynamixel.moveSpeed(16,200,x);
  Dynamixel.moveSpeed(14,200,x);
  delay(500);
  Dynamixel.moveSpeed(4,700,x);
   Dynamixel.moveSpeed(9,700,x);
   Dynamixel.moveSpeed(16,300,x);
   delay(500);
   Dynamixel.moveSpeed(2,700,pelan);
   Dynamixel.moveSpeed(7,500,pelan);
   Dynamixel.moveSpeed(14,400,pelan);
}
 
void jalan (){
maju3kaki_1();

maju3kaki_2();
}

void mundur (){
mundur3kaki_1();

mundur3kaki_2();
}

void belok_kiri (){
belok3kaki_1();

belok3kaki_2();
}

void loop(){
//jalan();
//delay(10000);
//jongkok();
//mundur();
//delay(10000);
//maju3kaki_2();
//belakang_kanan();
//belakang_kiri();
belok_kiri ();
}
