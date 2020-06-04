
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
PowerSource Battery(A1, 8);
PowerSource SolarPanel(A2, A0);

void setup() {
}

void loop() {

}
