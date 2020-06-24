
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
int i;

boolean TimerRunning = false;
uint32_t lastMillis;

void fault() {
  Buzzer.on();
  SolarPanel.disable();
  Fan.on();
  Red.blinkfast();
  Serial.println("Battery Voltage Not Within Limits");
}

bool CheckTimer(unsigned long TimeOut) {
  if (TimerRunning && (millis() - lastMillis >= TimeOut * 1000))
  {
    TimerRunning = false;
    Serial.println("Timer End");
    return true;
  }
  else
  { if (debug == true) {
      Serial.println("Timer Ticking");
    }
    return false;
  }
}

void StartTimer() {
  if (!TimerRunning)
  {
    lastMillis = millis();
    TimerRunning = true;
    Serial.println("Timer Started");
  }
}
void setup() {
  Serial.begin(9600);
  //batterydisable (feature removed in hardware)
  SolarPanel.disable();
  Fan.off();
  Buzzer.off();
  Charger.floatEnable();    // for added safety
  Serial.println("----------------- Arduino Charge Controller V1.0 ------------ ");


  delay(5000);


  BatteryVoltage = Battery.rawVoltage() * (5.0 / 1024.0) * BatteryMultiplier;

  for (i = 0; i < (int) BatteryVoltage; i++) {
    Blue.blinkslow();
  }

  delay(1000);

  BatteryVoltage = BatteryVoltage * 10;
  for (i = 0; i < (int)BatteryVoltage % 10; i++) {
    Red.blinkslow();
  }

  delay(5000);


}

void loop() {

  //FAN ON in case of constant current mode
  if (Charger.constantCurrent() == 1)
  {
    Fan.on();
  }

  BatteryVoltage = Battery.rawVoltage() * (5.0 / 1024.0) * BatteryMultiplier;

  if (debug == true) {
    Serial.print("BatteryVoltage = ");
    Serial.println(BatteryVoltage);
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

  if (BatteryVoltage > BatteryAbsorbMax + 0.5 || BatteryVoltage < 10) { // The offset can be removed if serial port connected
    fault(); // Solar Disconnect, Fan On , Buzzer On
  }

  else {
    //  if (PanelVoltage >= PanelMin && PanelVoltage <= PanelMax)  {
    if (PanelVoltage >= BatteryVoltage)  { //0.25 The offset can be reduced to 0.10V if serial port connected

      SolarPanel.enable();
      if (debug == true) {
        Serial.println("Panel Voltage Good");
      }

      /*  Constant Current Charging */
      if ( BatteryState <= 1 && BatteryVoltage <= 14.00) {    // Since module is not changing to CV mode even in float condition due to high current
        //    if ( BatteryState <= 1 || Charger.constantCurrent() == 1) {
        BatteryState = 1; //Constant Current
        Charger.floatDisable();
        //StartTimer();
        Blue.blinkfast();
        Fan.on();
        /*
           High Current hence Battery Voltage will be used as a measure to change to CV mode

              if ( Charger.constantCurrent() == 0) { // Disable loop if no proper load connected
                BatteryState = 2; //Constant Voltage
                Serial.println("Bulk Charging completed as charger changed to CV mode");
              }
        */
        /*
          else if ( CheckTimer(1800) == true) {   //Time in seconds
          BatteryState = 2; //Constant Voltage
          Serial.println("Bulk Charging ended by Plateu Timer");
          }
        */

        Serial.println("Bulk Charging in progress");


        if (BatteryVoltage > BatteryAbsorbMax)
        {
          Serial.println("Bulk Charging Voltage Higer than Expected");
          Buzzer.beep();
          Red.blinkfast();
        }
      }

      /*  Constant Voltage Charging */

      else if ( BatteryState <= 2) { // or timer for constant current ranout
        BatteryState = 2; //Constant Voltage
        Charger.floatDisable();
        StartTimer();
        Blue.blinkslow();
        Fan.on();

        if ( CheckTimer(900) == true) {    //Timer for Absorbtion Charge Termination is seconds
          BatteryState = 3; //Float Charging
          Serial.println("Absorbtion Charging ended by Timer");
        }
        else {
          Serial.println("Absorbtion Charging in progress");
        }
      }

      /*  Float Charging */

      else if ( BatteryState <= 3 ) {
        BatteryState = 3; //Float Charge
        Charger.floatEnable();
        Blue.on();
        Fan.fade();

        if (BatteryVoltage > BatteryFloatMax)
        {
          Serial.println("Float Charging Voltage Higer than Expected");
          Buzzer.beep();
          Red.blinkfast();
        }

        if (Charger.constantCurrent() == 1)
        {
          Serial.println("Constant Current Mode Triggered in Float Charging");
          Serial.println("Switching to Absorbtion Mode");
          BatteryState = 2; //Constant Voltage
          //Buzzer.beep();
          //Red.blinkfast();
        }
        else {
          Serial.println("Float Charging in progress");
        }

      }
      else {
        Serial.println("No Charging Cycle in progress");
      }

    }
    else {
      Serial.println("Panel Voltage Low hence Pannel Disconnected");
      SolarPanel.disable();
      Fan.off();
      Blue.off();
      Red.blinkslow();
      TimerRunning = false;
    }
  }
}
