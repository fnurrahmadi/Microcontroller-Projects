#include <LCD03.h>
#include <Keypad.h>

/*
   FLEXIBLE ROOM-SECURITY SYSTEM
*/

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'},
};
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {8, 7, 6};
Keypad keyinput = Keypad(makeKeymap(keys), rowPINS, colPINS, ROWS, COLS);

int main1 = 0;
int main2 = 0;
int main3 = 0;

void setup() {
  Serial.begin(9600);
}

int GetNumber() {
  int num = 0;
  char key1 = keyinput.getKey();
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

  
  
  mainmenu = GetNumber();
  
  main2 = GetNumber();
  
  main3 = GetNumber();
  

  if (v1 == 1) && (v2 == 1) && (v3 == 1) {

  }
  else if () {

  }
  else if () {

  }
}
