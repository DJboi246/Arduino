#include "SevSeg.h"
#include <Keypad.h>

bool iscode=false;
byte numDigits = 4;
byte digitPins[] = {49, 48, 47, 46};
byte segmentPins[] = {29, 22, 23, 25, 26, 28, 27, 24};
const int ledpin = 40;
const int buzzerpin = 30;
const int buttonpin = 52;
const int motorpin =  53;
const byte ROWS = 4;
const byte COLS = 4;
byte rowPins[ROWS] = {11, 10, 9, 8};
byte colPins[COLS] = {7, 6, 5, 4};
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
char password [4] = { '2', '4', '6', '8'};
int current_index = 0;
char entered_code [4] = {'0', '0', '0', '0'};
SevSeg sevseg;
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(ledpin, OUTPUT);
  pinMode(buzzerpin, OUTPUT);
  pinMode(motorpin, OUTPUT);
  pinMode(buttonpin, INPUT);
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, true);
  sevseg.setBrightness(90);
  Serial.begin(9600);
}

void loop() {
  if (iscode==false && digitalRead(buttonpin)==HIGH){
      digitalWrite(buzzerpin, HIGH);
      delay(2000);
      digitalWrite(buzzerpin, LOW);
  }
  sevseg.setNumber((entered_code[0] - '0') * 1000 + (entered_code[1] - '0') * 100 + (entered_code[2] - '0') * 10 + entered_code[3] - '0', 0);
  sevseg.refreshDisplay();
  char customkey = customKeypad.getKey();

  if (customkey) {

    if (customkey == '*' && current_index != 0) {

      current_index = current_index - 1;
      entered_code[current_index] = '0';

    } else if (customkey == '#' && current_index == 4) {
      iscorrect();
    } else if (customkey != 'A' && customkey != 'B' && customkey != 'C' && customkey != 'D' && customkey != '#' && customkey != '*' && current_index != 4) {
      entered_code[current_index] = customkey;
      current_index = current_index + 1;
    }
  }

}

void iscorrect() {
  if (entered_code[0] - 48 == password[0] - 48 && entered_code[1] - 48 == password[1] - 48 && entered_code[2] - 48 == password[2] - 48 && entered_code[3] - 48 == password[3] - 48) {
    digitalWrite(ledpin, HIGH);
    delay(500);
    digitalWrite(ledpin, LOW);
    iscode=true;
    for (int i = 0; i < 10; i++) {
      if (digitalRead(buttonpin)==HIGH){
        digitalWrite(motorpin,HIGH);
        break;
        break;
      }
      delay(1000);
    }
   iscode=false;
  }
}
