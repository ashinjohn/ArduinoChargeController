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
  delay(250);
}

void OUTPUTS::off()
{
  digitalWrite(_pin, LOW);
  delay(250);
}
