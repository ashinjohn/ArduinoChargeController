/*
  OUTPUTS.cpp - Library for Digital Outputs
  Created by abjohn.  June 3, 2020.
*/
#include "Arduino.h"
#include "OUTPUTS.h"

OUTPUTS::OUTPUTS(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void OUTPUTS::on()
{
  digitalWrite(_pin, HIGH);
  delay(50);
}

void OUTPUTS::off()
{
  digitalWrite(_pin, LOW);
  delay(50);
}

void OUTPUTS::beep()
{
  digitalWrite(_pin, HIGH);
  delay(100);
  digitalWrite(_pin, LOW);
  delay(100);
}

void OUTPUTS::fade()
{
  analogWrite(_pin, 120);
  delay(50);
}