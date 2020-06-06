/*
  Charger.cpp - Library for Charger Mode Detection (CC/CV) and Float Charge 
  Created by abjohn.  June 3, 2020.
*/
#include "Arduino.h"
#include "Charger.h"

Charger::Charger(int inPin,int outPin)
{
  //pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
  pinMode(inPin, INPUT_PULLUP);
  _inPin = inPin;
  _outPin = outPin;
}

int Charger::constantCurrent()
{
  return digitalRead(_inPin);
}

void Charger::floatEnable()
{
  digitalWrite(_outPin, HIGH);
  delay(250);
}

void Charger::floatDisable()
{
  digitalWrite(_outPin, LOW);
  delay(250);
}
