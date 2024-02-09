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

/*//LCD 20x4 LIBRARY
  #include <Wire.h> // For I2C
  #include <LCD.h> // For LCD
  #include <LiquidCrystal_I2C.h> // Added library*
  LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);
*/

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

//ACTIVATION VARIABLES
int AlarmActive = 0;

void setup() {
  Serial.begin(9600);   // Initiate a serial communication

  //RFID SETUP
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

  //LCD SETUP
  //lcd.begin(20,4)
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

void ActivationMenu() {
  /*
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("--Activation Menu---");
    lcd.setCursor(0,1);
    lcd.print("1. Fully Activate");
    lcd.setCursor(0,2);
    lcd.print("2. Bypass Rooms");
    lcd.setCursor(0,3);
    lcd.print("3. Back");
  */
  int menu2 = GetNumber();
  Serial.println(menu2);
  if (menu2 == 1) {

  }
  else if (menu2 == 2) {

  }
  else if (menu2 == 3) {

  }
  else {

  }
}

void DeactivationMenu() {

}

//PRINTING MAINMENU ON LCD AND USING GETNUMBER FUNCTION TO CHOOSE OPTION
void MainMenu() {
  /*lcd.setCursor(0,1);
    lcd.print("-----Main Menu------");
    lcd.setCursor(0,2);
    lcd.print("1. Activation Menu");
    lcd.setCursor(0,3);
    lcd.print("2. Deactivation Menu");
  */
  int menu1 = GetNumber();
  Serial.println(menu1);
  if (menu1 == 1) {
    ActivationMenu();
  }
  else if (menu1 == 2) {
    //DeactivationMenu();
  }
  else {

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
    delay(2000);
    /*lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Welcome, User!");
    */
    MainMenu();
  }
  else if (content.substring(1) == "1E 48 E1 1B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(2000);
    MainMenu();
    /*lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Welcome, Fakhri!");
    */
  }
  else
  {
    Serial.println("Access denied");
    Serial.println();
    /*lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("------Error!------");
      lcd.setCursor(0,1);
      lcd.print("Unauthorized Tag");
      lcd.setCursor(0,2);
      lcd.print("Please Tap Again");
    */
    delay(2000);
  }
}

void loop() {
  /*lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("please tap your ID");
  */
  RFIDstart();
}
