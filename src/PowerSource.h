/*
  PowerSource.h - Library for Power Source like PowerSource Panel And Battery
  Created by abjohn.  June 3, 2020.
*/
#ifndef PowerSource_h
#define PowerSource_h

#include "Arduino.h"

class PowerSource
{
  public:
    PowerSource(int pin,int analogPin);
  private:
    int _pin;
    int _analogPin;
    float rawVoltage();
    void enable ();
    void disable ();
};

#endif