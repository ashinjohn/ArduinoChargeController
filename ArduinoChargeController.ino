
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
#include "src/Charger.h"


/* PIN INITIALISATION */
LED Red(13);
LED Blue(12);
OUTPUTS Buzzer(9);
OUTPUTS Fan(10);
PowerSource Battery(8, A1);
PowerSource SolarPanel(A0, A2);
Charger Charger(A3,11);
  
/* Configurations */
const float BatteryMultiplier = 3.006; //(98.5 + 49.1)*49.1  Voltage Divider Multiplier for Battery
const float PanelMultiplier = 6.0482;  //(99.45 +19.7) Voltage Divider Multiplier for Battery
volatile float BatteryVoltage = 0;
volatile float PanelVoltage = 0;
const bool debug = true;
int BatteryState=0; // 0 - Discharged, 1 - Constant Current,  2- Constant Voltage , 3 - Float Charge 
float BatteryTooLow = 11.00; // ( Beep to indicate Battery Low)
float BatteryReconnect = 11.7; //11.6 (Exact Value)
float BatteryFloat = 13.6; //13.8 (Exact Value)
float BatteryAbsorb = 14.2; //14.4 (Exact Value)

void setup() {
  Serial.begin(9600);
  //batterydisable
  //solardisable
  //fandisable
  //buzzerdisable
}

void loop() {
SolarPanel.enable();
/*
Charger.floatDisable(); 
Battery.disable();
delay(3000);
Red.blinkfast();
Battery.enable();
delay(3000);
Red.blinkfast();
*/
Battery.enable();

Charger.floatEnable();  // needs to check transistor
delay(3000);
Red.blinkfast();
Charger.floatDisable();  // needs to check transistor
delay(3000);
Red.blinkfast();

Serial.println(Charger.constantCurrent());

  /*
    BatteryVoltage=Battery.rawVoltage()*BatteryMultiplier*(5.0/1024.0);
    if (debug==true){  Serial.print("BatteryVoltage = ");Serial.println(BatteryVoltage);}
    delay(100);

    PanelVoltage=SolarPanel.rawVoltage()*PanelMultiplier*(5.0/1024.0);
    if (debug==true){  Serial.print("PanelVoltage = "); Serial.println(PanelVoltage);}
    delay(100);
  */

  /*
    if(PanelVoltage>BatteryVoltage)
    {
    /floatdisable ie. Enable Constant current charging
    //enable solar
    //
    //check for constant current. ie start timer for constant current

    //if constant voltage . ie start timer for constant current

    //else float

      }
    else
    disablesolar
    disablebattery

  */
}
