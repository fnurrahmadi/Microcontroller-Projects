//PINOUTS
/* Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
   USE 3.3V FOR RFID!!!!!
*/
/* Keypad Pin 1 –> Arduino Pin 43
   Keypad Pin 2 –> Arduino Pin 44
   Keypad Pin 3 –> Arduino Pin 45
   Keypad Pin 4 –> Arduino Pin 46
   Keypad Pin 5 –> Arduino Pin 47
   Keypad Pin 6 –> Arduino Pin 48
   Keypad Pin 7 –> Arduino Pin 49
*/

//RFID LIBRARY
#include <SPI.h>
#include <MFRC522.h>

//LCD 20x4 LIBRARY
#include <Wire.h> // For I2C
#include <LiquidCrystal_I2C.h> // Added library*
LiquidCrystal_I2C lcd(0x27, 20, 4);

//KEYPAD LIBRARY
#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {43, 44, 45, 46}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {47, 48, 49};    // connect to the column pinouts of the keypad
Keypad kypd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//RFID PINS
#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

/*//PIR SENSOR PINS
  int PirPin1 =
  int PirPin2 =
  int pirState = LOW;             // we start, assuming no motion detected
  int Pirval = 0;                    // variable for reading the pin status
  int
*/
//ULTRASONIC SENSOR PINS



//MILLIS VARIABLES
unsigned long interval = 5000; // the time we need to wait
unsigned long previousMillis = 0; // millis() returns an unsigned long.
unsigned long currentMillis = millis(); // grab current time

//ACTIVATION VARIABLES
int AlarmActive = 0;
int room1 = 1;
int room2 = 1;
int password = 1234;
int menu = 0;

void setup() {
  Serial.begin(9600);   // Initiate a serial communication

  //RFID SETUP
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

  //LCD SETUP
  lcd.init();
  lcd.backlight();
  lcd.setCursor(6, 0);
  lcd.print("Welcome");
  lcd.setCursor(2, 1);
  lcd.print("Guaranteeing You");
  lcd.setCursor(0, 2);
  lcd.print("Safety & Flexibility");
  lcd.setCursor(0, 3);
  lcd.print("HIDIOUS Alarm System");
  delay(5000);
  lcd.clear();
}

//FUNCTION USED TO GET ANY KEYPAD INPUT
int GetNumber() {
  int num  = 0;
  char key = kypd.getKey();
  while (key != '#')
  {
    switch (key)
    {
      case NO_KEY:
        break;

      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        Serial.println(key);
        num = num * 10 + (key - '0');
        break;

      case '*':
        num = 0;
        break;
    }
    key = kypd.getKey();
  }
  return num;
}

//PRINTING PASSWORDMENU ON LCD AND USING GETNUMBER FUNCTION TO CHOOSE OPTION
void PasswordMenu() {
  lcd.setCursor(2, 0);
  lcd.print("Please Input The");
  lcd.setCursor(2, 1);
  lcd.print("Correct Password");
  lcd.setCursor(0, 3);
  lcd.print("3. Exit");

  menu = GetNumber();
  Serial.println(menu);
  if (menu == 3) {
    lcd.clear();
    MainMenu();
  }
  else if (menu != password) {
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("PASSWORD INCORRECT");
    PasswordMenu();
  }
  else {
    lcd.clear();
  }
}

//PRINTING BYPASSMENU ON LCD AND USING GETNUMBER FUNCTION TO CHOOSE OPTION
void BypassMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("----Bypass Menu-----");
  lcd.setCursor(0, 1);
  lcd.print("1. ToggleRoom1 =");
  lcd.setCursor(17, 1);
  if (room1 == 1) {
    lcd.print("ON");
  }
  else {
    lcd.print("OFF");
  }
  lcd.setCursor(0, 2);
  lcd.print("2. ToggleRoom2 =");
  lcd.setCursor(17, 2);
  if (room2 == 1) {
    lcd.print("ON");
  }
  else {
    lcd.print("OFF");
  }
  lcd.setCursor(0, 3);
  lcd.print("3. Back");

  menu = GetNumber();
  Serial.println(menu);
  if (menu == 1) {
    if (room1 == 1) {
      room1 = 0;
    }
    else {
      room1 = 1;
    }
    BypassMenu();
  }
  else if (menu == 2) {
    if (room2 == 1) {
      room2 = 0;
    }
    else {
      room2 = 1;
    }
    BypassMenu();
  }
  else if (menu == 3) {
    ActivationMenu();
  }
  else {
    lcd.clear();
    BypassMenu();
  }
}

//PRINTING ACTIVATIONMENU ON LCD AND USING GETNUMBER FUNCTION TO CHOOSE OPTION
void ActivationMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("--Activation Menu---");
  lcd.setCursor(0, 1);
  lcd.print("1. Activate");
  lcd.setCursor(0, 2);
  lcd.print("2. Bypass Rooms");
  lcd.setCursor(0, 3);
  lcd.print("3. Back");

  menu = GetNumber();
  Serial.println(menu);
  if (menu == 1) {
    lcd.clear();
    PasswordMenu();
    AlarmActive = 1;
  }
  else if (menu == 2) {
    BypassMenu();
  }
  else if (menu == 3) {
    lcd.clear();
    MainMenu();
  }
  else {
    ActivationMenu();
  }
}

//PRINTING DEACTIVATIONMENU ON LCD AND USING GETNUMBER FUNCTION TO CHOOSE OPTION
void DeactivationMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Deactivation Menu");
  lcd.setCursor(0, 1);
  lcd.print("1. Deactivate");
  lcd.setCursor(0, 3);
  lcd.print("3. Back");

  menu = GetNumber();
  Serial.println(menu);
  if (menu == 1) {
    lcd.clear();
    PasswordMenu();
    AlarmActive = 0;
  }
  else if (menu == 3) {
    lcd.clear();
    DeactivationMenu();
  }
  else {
    DeactivationMenu();
  }
}

//PRINTING MAINMENU ON LCD AND USING GETNUMBER FUNCTION TO CHOOSE OPTION
void MainMenu() {
  lcd.setCursor(0, 1);
  lcd.print("-----Main Menu------");
  lcd.setCursor(0, 2);
  lcd.print("1. Activation");
  lcd.setCursor(0, 3);
  lcd.print("2. Deactivation");

  menu = GetNumber();
  Serial.println(menu);
  if (menu == 1) {
    ActivationMenu();
  }
  else if (menu == 2) {
    DeactivationMenu();
  }
  else {
    lcd.clear();
    MainMenu();
  }
}

//READING RFID AUTHENTICATIONS
void RFIDstart() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

  if (content.substring(1) == "BE 84 BE 79") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome, User!");
    MainMenu();
  }
  else if (content.substring(1) == "1E 48 E1 1B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome, Fakhri!");
    MainMenu();
  }
  else
  {
    Serial.println("Access denied");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("**Unauthorized Tag**");
  }
}

void loop() {

  currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    previousMillis = millis();
  }

  if (AlarmActive == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Alarm: Activated");
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("Alarm: Deactivated");
  }
  lcd.setCursor(0, 3);
  lcd.print("Please Tap Your ID");

  RFIDstart();

  //ALARM CONDITIONS
  if (AlarmActive == 1) {
    if (room1 == 1 && room2 == 1) {

    }
    else if (room1 == 1) {

    }
    else if (room2 == 1) {

    }
    else {

    }
  }
}
