#include "IRremote.hpp"

int recpin=50;
int buzpin=51;
int senspin=49;
int curcommand=22;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzpin,OUTPUT);
  pinMode(senspin,INPUT);
  IrReceiver.begin(recpin);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (IrReceiver.decode()){
    IrReceiver.resume();
    if (IrReceiver.decodedIRData.command==12){
      curcommand=12;
    }
    if (IrReceiver.decodedIRData.command==22){
      curcommand=22;
    }
  }
  if (curcommand==12 && digitalRead(senspin)==HIGH){
    digitalWrite(buzpin,HIGH);
  }else{
    digitalWrite(buzpin,LOW);
  }
}
