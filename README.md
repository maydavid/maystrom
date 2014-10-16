# maystrøm


open modular camper automation system

## bc1

**bus control:**  

This is the main controller. It is used for interacting with the user, controlling actuators, reading sensors, power management and so on. Right now it is build around a FRDM-KL46Z board with a Cortex-M0+ running at 48 MHz. It's firmware is developed using the mbed SDK.

The current *breadboard* prototype consists of:
  * NHD-24-320240 TFT to display data
  * RedBearLab BLE mini to allow for control and sensing via BLE enabled smartphones
  * Rotary encoder for user interaction


## bp1

**bus power:**

Used for switching and sensing the main 12V input. Furthermore it generates the 3.3V used for the uC and the the onboard current sensor. The main 12V rail is switched with a relay controlled by the µC on the **bc** module. The current flowing to the loads is sensed using a ACS711. The voltage cn be senses with the help of a simple voltage divider. 

## cm1

**control module:**  

This module is capable of switching and dimming high voltage loads. Multiple of these can be connected to **bc1** and **bp1**. The modules have a pwm input that allows to to dim lights for instance. The modules can be equipped with a voltage regulator to ensure a steady 12V output even at engine startup or while driving. If not needed (usually the case for automotive accessories) they can be bypassed with a solder bridge.



