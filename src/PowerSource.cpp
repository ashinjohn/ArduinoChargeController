/*
  PowerSource.cpp - Library for Power Source like PowerSource Panel And Battery
  Created by abjohn.  June 3, 2020.
*/
#include "Arduino.h"
#include "PowerSource.h"

PowerSource::PowerSource(int pin,int analogPin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
  analogPin = analogPin;
}

float PowerSource::rawVoltage()
{
  return analogRead(analogPin);
}

void PowerSource::enable()
{
  digitalWrite(_pin, HIGH);
  delay(250);
}

void PowerSource::disable()
{
  digitalWrite(_pin, LOW);
  delay(250);
}
