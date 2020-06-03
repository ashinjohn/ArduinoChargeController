# **Arduino Charge Contoller**
Regulates the Output Voltage of XL4016 Buck Regulator using an Arduino Uno.

IDE - Arduino
MCU - Arduino Uno R3 with Custom Shield for measuring voltage and adjusting Battery Charging Voltage

## **Hardware Design**
1.Battery Voltage Mesurement using internal ADC
2.Solar Panel Voltage Mesurement using internal ADC
3.Soloar Panel Disconnect in case of Low Voltage( prevents back feeding during night)
4.Battery Charge Voltage Adjustment to Float Voltage
5.Charging disable option for measuring battery voltage 
6.2 PWM Outputs for connecting Buzzer,Relay or FAN 
7.2 LEDs for indicating status
8. Current Sensor and Digipot for MPPT ( Pending )
9. CC/CV mode input from XL4016 Buck Regulator.

## **Firmware**
1.Voltage Measurement using internal ADC
2.Software Timer for disabling charging ( Plateau timer) 
3.Switching to float charging after CV charge current has tapered down
4.Debug Messages via Serial.
5.Panel Voltage and Battery Voltage output on Serial port for pushing to Cloud ( Pending )
