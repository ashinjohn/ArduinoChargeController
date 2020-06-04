/*
  Charger.h - Library for Charger Mode Detection (CC/CV) and Float Charge 
  Created by abjohn.  June 3, 2020.
*/
#ifndef Charger_h
#define Charger_h

#include "Arduino.h"

class Charger
{
  public:
    PowerSource(int inPin,int outPin);
    int constantCurrent();
    void floatEnable ();
    void floatDisable ();
  private:
    int _inPin;
    int _outPin;
};

#endif