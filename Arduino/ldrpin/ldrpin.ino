// header
//lbraries

const int ldrpin = 13;
int relaypin = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (ldrpin, INPUT);

  pinMode (relaypin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ldrvalue = digitalRead(ldrpin);
  Serial.println(ldrvalue);
  delay(1000);

  // if there is light = relay ON
  // else (there is no light/dark) = relay OFF

  if(ldrvalue == 0) {
    digitalWrite(relaypin, HIGH);
  }
  else {
    digitalWrite(relaypin, LOW); 
  }

  /*digitalWrite(relaypin, HIGH);
  delay(1000);
  digitalWrite(relaypin, LOW);
  delay(1000);
  */
}
