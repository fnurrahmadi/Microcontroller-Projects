char p1 = '1';
char p2 = '0';
char p3 = '1';
char p4 = '1';
char p5 = '0';
char p6 = '0';
char p7 = '1';
char p8 = '0';

String sensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor = String(p1)+String(",")+String(p2)+String(",")+String(p3)+String(",")+String(p4)+String(",")+String(p5)+String(",")+String(p6)+String(",")+String(p7)+String(",")+String(p8);

  //Serial.print("sensor: ");
  Serial.println(sensor);
  delay(1000);
}
