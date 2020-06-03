/*
  LED.h - Library for flashing LEDs
  Created by abjohn.  June 3, 2020.
*/
#ifndef LED_h
#define LED_h

#include "Arduino.h"

class LED
{
  public:
    LED(int pin);
    void on();
    void off();
    void blinkfast();
    void blinkslow();
  private:
    int _pin;
};

#endif