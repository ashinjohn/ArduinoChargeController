
/*
   Arduino Charge Controller
   Description: Arduino based charge controller for Solar Systems that Regulates the Output Voltage of XL4016 Buck Regulator.
   Firmware fine tuned for 100W Solar Panel and 12V Lead Acid Battery
   IDE -> Arduino
   MCU - Arduino Uno R3 with Custom Shield for measuring voltage and adjusting Battery Charging Voltage

   Created by abjohn.  June 3, 2020.
*/

#include "src/LED.h"
#include "src/OUTPUTS.h"
#include "src/PowerSource.h"


/* PIN INITIALISATION */
LED Red(13);
LED Blue(12);
OUTPUTS Buzzer(9);
OUTPUTS Fan(10);
PowerSource Battery(8,A1);
PowerSource SolarPanel(A0,A2);

/* Configurations */
const float BatteryMultiplier = 3.006 ;//(98.5 + 49.1)  49.1;Voltage Divider Multiplier for Battery
const float PanelMultiplier = (99.45 + 4.9) / 4.9; //Voltage Divider Multiplier for Battery

void setup() {
  Serial.begin(9600);
}

void loop() {
//  Serial.println((Battery.rawVoltage()*BatteryMultiplier*(5.0/1024.0)));
  delay(100);
}
