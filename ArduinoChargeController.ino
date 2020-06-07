
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
Charger Charger(A3, 11);

/* Configurations */
const float BatteryMultiplier = 3.056; //(98.5 + 49.1)*49.1 =3.006 Voltage Divider Multiplier for Battery
const float PanelMultiplier = 6.1182;  //(99.45 +19.7) =6.0482 Voltage Divider Multiplier for Battery
volatile float BatteryVoltage = 0;
volatile float PanelVoltage = 0;
const bool debug = true;
int BatteryState = 0; // 0 - Discharged, 1 - Constant Current,  2- Constant Voltage , 3 - Float Charge
const float BatteryTooLow = 11.00; // ( Beep to indicate Battery Low)
const float BatteryReconnect = 11.6;
const float BatteryFloatMax = 13.8; //13.6 (Exact Value)
const float BatteryAbsorbMax = 15; //14.4 (Exact Value)
const float PanelMin = 15.0;
const float PanelMax = 24.0;

const float BatteryMin = 13.0;

int faultcount = 0;

void fault() {
  //faultcount++;
  Buzzer.on();
  SolarPanel.disable();
  Fan.on();
  Red.blinkfast();
  Serial.print("Fault");
}

void setup() {
  Serial.begin(9600);
  //batterydisable (feature removed in hardware)
  //solardisable
  //fandisable
  //buzzerdisable
  //floatenable // to keep battery safe
}

void loop() {
  BatteryVoltage = Battery.rawVoltage() * (5.0 / 1024.0) * BatteryMultiplier;//;

  if (debug == true) {
    Serial.print("BatteryVoltage = ");
    Serial.println(BatteryVoltage);
  }

  if (BatteryVoltage > BatteryAbsorbMax || BatteryVoltage < 10) { //False Triggering in startup needs to check
    fault();
  }

  delay(100);

  PanelVoltage = SolarPanel.rawVoltage() * PanelMultiplier * (5.0 / 1024.0);
  if (debug == true) {
    Serial.print("PanelVoltage = ");
    Serial.println(PanelVoltage);
  }
  delay(50);

  if (BatteryVoltage <= BatteryMin ) {
    BatteryState = 0; //Discharged
    if (debug == true) {
      Serial.println("Battery Dicharging");
    }
  }

  if (PanelVoltage >= PanelMin && PanelVoltage <= PanelMax)  {

    if (debug == true) {
      Serial.println("Panel Voltage Good");
    }

    if ( BatteryState <= 1 && Charger.constantCurrent() == 1) {
      BatteryState = 1; //Constant Current
      Charger.floatDisable();
      Serial.println("Bulk Charging in progress");
      if (BatteryVoltage > BatteryAbsorbMax)
      {
        Serial.println("Bulk Charging Voltage Higer than Expected");
        Buzzer.beep();
        Red.blinkfast();
      }
    }
    else if ( BatteryState <= 2 && Charger.constantCurrent() == 0) { // or timer for constant current ranout
      BatteryState = 2; //Constant Voltage
      Charger.floatDisable();
      Serial.println("Absorbtion Charging in progress");
      if (BatteryVoltage > BatteryAbsorbMax)
      {
        Serial.println("Bulk Charging Voltage Higer than Expected");
        Buzzer.beep();
        Red.blinkfast();
      }
    }

    else if ( BatteryState <= 3 ) { // or timer for constant voltage ranout
      BatteryState = 3; //Float Charge
      Charger.floatEnable();
      Serial.println("Float Charging in progress");
      if (BatteryVoltage > BatteryFloatMax)
      {
        Serial.println("Bulk Charging Voltage Higer than Expected");
        Buzzer.beep();
        Red.blinkfast();
      }

    }
    else {
      Serial.println("No Charging Cycle in progress");
    }

  }
  else {
    if (debug == true) {
      Serial.println("Panel Voltage Low or Disconnected");
    }
    SolarPanel.disable();
  }
}
