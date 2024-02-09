int relaypin = 7;

void setup() {
  pinMode(relaypin, OUTPUT);
}

void loop() {
  digitalWrite(relaypin, LOW);
  delay(500);
  digitalWrite(relaypin, HIGH);
  delay(500);

}

