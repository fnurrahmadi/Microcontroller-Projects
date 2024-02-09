//Software Serial
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(2, 3); //RX, TX
char bdata = 0;

//Pin Motor
int motor1a = 6;
int motor1b = 5;
int motor2a = 10;
int motor2b = 9;

//Pin Ultrasonic
int trigPin = 13;
int echoPin = 12;
int cm;
int warning, warned;

int motorSpeed = 10; // Atur Speed Motor

//Fungsi Menggerakkan Motor
void gerakMotor(bool gerak1, bool gerak2, bool gerak3, bool gerak4){
  digitalWrite(motor1a, gerak1);
  digitalWrite(motor1b, gerak2);
  digitalWrite(motor2a, gerak3);
  digitalWrite(motor2b, gerak4);
}

//Fungsi Membaca Sensor Ultrasonic
int pingSensor(int trig, int echo){
  long duration;
  int distance;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration*0.034)/2;
  return distance;
}

void setup() {
  bluetooth.begin(9600);
  //Serial.begin(9600);
  pinMode(motor1a, OUTPUT);
  pinMode(motor1b, OUTPUT);
  pinMode(motor2a, OUTPUT);
  pinMode(motor2b, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(50);
}

void loop() {
  //Baca Sensor dan Menampilkan Output
  cm = pingSensor(trigPin, echoPin);
  //Serial.print("distance: ");
  //Serial.print(cm);
  //Serial.println(" cm");
  
  //Kondisi Warning
  if(cm < 100){
    warning = 1;
  }
  else{
    warning = 0;
  }
  
  //Kondisi Pengiriman Warning ke Aplikasi
  if(warning == 0 && warned == 1){
    bluetooth.write('1');
    //Serial.println("Safe");
    delay(10);
    warned = 0;
  }
  else if(warning == 1 && warned == 0){
    bluetooth.write('2');
    //Serial.println("Warning");
    delay(10);
    warned = 1;
  }

  //Menerima Data Dari Bluetooth
  if(bluetooth.available() > 0){
    bdata = bluetooth.read();
    //Serial.println(bdata);

    //Kondisi Gerak Motor berdasarkan Data Bluetooth
    if(bdata == 'A'){
      gerakMotor(motorSpeed, LOW, motorSpeed, LOW);
      //Serial.println("Maju");
    }
    else if (bdata == 'B'){
      gerakMotor(motorSpeed, LOW, LOW, motorSpeed);
      //Serial.println("Kanan");
    }
    else if (bdata == 'C'){
      gerakMotor(LOW, motorSpeed, LOW, motorSpeed);
      //Serial.println("Mundur");
    }
    else if (bdata == 'D'){
      gerakMotor(LOW, motorSpeed, motorSpeed, LOW);
      //Serial.println("Kiri");
    }
    else if(bdata == '0'){
      gerakMotor(LOW, LOW, LOW, LOW);
      //Serial.println("Stop");
    }
  }
  delay(10);
}
