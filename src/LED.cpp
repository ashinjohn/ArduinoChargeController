/*
  LED.cpp - Library for flashing LEDs
  Created by abjohn.  June 3, 2020.
*/
#include "Arduino.h"
#include "LED.h"

LED::LED(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void LED::on()
{
  digitalWrite(_pin, HIGH);
  delay(250);
}

void LED::off()
{
  digitalWrite(_pin, LOW);
  delay(250);
}

void LED::blinkfast()
{
  digitalWrite(_pin, HIGH);
  delay(10);
  digitalWrite(_pin, LOW);
  delay(10);
}

void LED::blinkslow()
{
  digitalWrite(_pin, HIGH);
  delay(300);
  digitalWrite(_pin, LOW);
  delay(300);
}