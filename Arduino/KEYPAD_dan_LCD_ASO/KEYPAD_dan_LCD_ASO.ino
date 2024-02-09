#include <Keypad.h>
//#include <LiquidCrystal.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {43, 44, 45, 46}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {47, 48, 49};    // connect to the column pinouts of the keypad
Keypad kypd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//LiquidCrystal lcd(22, 2, 3, 26, 4, 30);

int v1 = 0;

void setup(){
  Serial.begin(9600);
}


int GetNumber(){
  int num  = 0;
  char key = kypd.getKey();
  while(key != '#')
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


void loop(){
  v1 = GetNumber();
  
  Serial.println(v1);

  if (v1==14){
    Serial.println("Selamat Datang  ");
    Serial.println("TV anda 14 Inch ");
  }
  else if (v1==17){
    Serial.println("Selamat Datang  ");
    Serial.println("TV anda 17 Inch ");
  }
  else if (v1==20){
    Serial.println("Selamat Datang  ");
    Serial.println("TV anda 20 Inch ");
  }
  else if (v1==21){
    Serial.println("Selamat Datang  ");
    Serial.println("TV anda 21 Inch ");
  }
}
