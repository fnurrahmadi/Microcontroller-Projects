#define Echo_Parkir_A 3
#define Trig_Parkir_A 4
#define Echo_Parkir_B 5
#define Trig_Parkir_B 6
#define 

long durasi, Jarak_Parkiran_A, Jarak_Parkiran_B;

void  Parkiran_A(){
    digitalWrite (Trig_Parkir_A, LOW);
    delayMicroseconds(8);
    digitalWrite (Trig_Parkir_A, HIGH);
    delayMicroseconds(8);
    digitalWrite (Trig_Parkir_A, LOW);
    delayMicroseconds(8);
    durasi = pulseIn(Echo_Parkir_A, HIGH);
    Jarak_Parkiran_A = (durasi/2)/29.1;
}

void Parkiran_B(){
    digitalWrite (Trig_Parkir_B, LOW);
    delayMicroseconds(8);
    digitalWrite (Trig_Parkir_B, HIGH);
    delayMicroseconds(8);
    digitalWrite (Trig_Parkir_B, LOW);
    delayMicroseconds(8);
    durasi = pulseIn(Echo_Parkir_B, HIGH);
    Jarak_Parkiran_B = (durasi/2)/29.1;
    Serial.print(Jarak_Parkiran_B);
    Serial.println(" cm");
}

void setup() {
pinMode (Trig_Parkir_A, OUTPUT);
pinMode (Echo_Parkir_A, INPUT);
pinMode (Trig_Parkir_B, OUTPUT);
pinMode (Echo_Parkir_B, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Jarak_Parkiran_B <= 6 ){
      Serial.print("Parkiran A Sudah di Tempati");
  }
  else {
    Serial.print(Jarak_Parkiran_A);
    Serial.println(" cm");
  }
}
