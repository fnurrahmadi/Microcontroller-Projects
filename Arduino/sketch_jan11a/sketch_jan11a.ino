#include <Servo.h>

Servo servo_test; //inisialisasi servo yang terhubung
int suhu;
int angle = 0;
int potentio0 = A0; //inisialisasi analog pin A0 untuk potensiometer
int potentio1 = A1;
double setpoint, error, lasterror, deltaSERVO;
int Kp=0.5, Ki=0, Kd=0;
int angleservo = 9;

void setup() {
servo_test.attach(9); //menyambungkan pin sinyal servo ke pin9 arduino
#define pinMode(potentio0, INPUT);
#define pinMode(potentio1, INPUT);  
#define pinMode(angle, OUTPUT);
}

void loop() {
  servo_test.attach(9); //menyambungkan pin sinyal servo ke pin9 arduino
  suhu = analogRead(potentio0); //membaca nilai potentiometer antara 0 - 1023
  angle = map(suhu, 0, 1023, 0, 180); //scaling nilai potensiometer ke derajat servo 0 - 180
  servo_test.write(angle); //untuk merotasi servo ke derajat yang ditetapkan
  deltaSERVO = (Kp*error);
  setpoint = analogRead(potentio1);
  setpoint = map(setpoint, 0, 1023, 0, 180);
  error = abs(setpoint - suhu);
  
  }
if(setpoint <= 30)  {
  while(error!=lasterror) {
    angle=+deltaSERVO;
    analogWrite(angleservo, 30);
    lasterror=error;
  }
}
else if(setpoint <= 45)  {
  while(error!=lasterror) {
    angle=+deltaSERVO;
    analogWrite(angleservo, 45);
    lasterror=error;
  }
}
else if(setpoint > 45)  {
  while(error!=lasterror) {
    angle=+deltaSERVO;
    analogWrite(angleservo, 60);
    lasterror=error;
  }
}

