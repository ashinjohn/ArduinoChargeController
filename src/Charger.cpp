/*
  Charger.cpp - Library for Charger Mode Detection and Float Mode
  Created by abjohn.  June 3, 2020.
*/
#include "Arduino.h"
#include "Charger.h"

Charger::Charger(int inPin,int outPin)
{
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
  _pin = pin;
  _analogPin = analogPin;
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

void Charger::FloatDisable()
{
  digitalWrite(_outPin, LOW);
  delay(250);
}
