#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'},
};
byte rowPINS[ROWS] = {5,4,3,2};
byte colPINS[COLS] = {8,7,6};
Keypad keypad = Keypad(makeKeymap(keys), rowPINS, colPINS, ROWS, COLS);

int v1 = 0;
int v2 = 0;
int v3 = 0;

void setup() {
  Serial.begin(9600);
}

int GetNumber() {
  int num = 0;
  char key1 = keypad.getKey();
  switch (key1)
   {
     case NO_KEY:
      break;

    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
      lcd.print(key1);
      num = num * 10 + (key1 - '0');
      break;

    case '#':
        return num;
        break;

    case '*':
        num = 0;
        lcd.clear();
   }
}

void loop() {
  v1 = GetNumber();
  lcd.print(v1);
  v2 = GetNumber();
  lcd.print(v2);
  v3 = GetNumber();
  lcd.print(v3);

  if(v1==1)&&(v2==1)&&(v3==1) {
    
  }
  else if() {
    
  }
  else if() {
    
  }
}
