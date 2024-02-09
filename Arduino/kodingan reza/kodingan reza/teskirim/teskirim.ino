#include <SoftwareSerial.h>

SoftwareSerial arduinoSerial(10, 11); // RX, TX

void setup() {
  arduinoSerial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  float suhu = 12.7 ;
  int BPM = 13 ;
  int IBI = 1333;
  String str = String('<')+String(suhu)+String(',')+String(BPM)+String(',')+String(IBI)+String('>');
  arduinoSerial.print(str);
  delay(1000);

}
