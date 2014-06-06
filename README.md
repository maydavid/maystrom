# maystrøm


open modular camper automation and infotainment system

## bc1

**bus control:**  
This is the main controller. It is used for interacting with the user, controlling actuators, reading sensors, power management.


## bp1

**bus power**
Used for switching and sensing the main 12V input. Generation of 3.3V used for the uC. 

## cm1

**control module:**  
This module is capable of switching and dimming high voltage loads. Multiple of these can be connected to **bc1** and **bp1**



