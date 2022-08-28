#define AUDIO_IN_PIN    35

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(AUDIO_IN_PIN);
  Serial.println(sensorValue);
  delay(100);
}
