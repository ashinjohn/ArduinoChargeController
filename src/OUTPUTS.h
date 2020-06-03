/*
  OUTPUTS.h - Library for Digital Outputs
  Created by abjohn.  June 3, 2020.
*/
#ifndef OUTPUTS_h
#define OUTPUTS_h

#include "Arduino.h"

class OUTPUTS
{
  public:
    OUTPUTS(int pin);
    void on();
    void off();
  private:
    int _pin;
};

#endif