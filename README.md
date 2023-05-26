# System Description 
The door locker system is an embedded system project that uses two microcontrollers, the HMI ECU and Control ECU, to provide secure access control. 

The Control ECU is responsible for validating the entered password from the user, saving the password in an external EEPROM, and sending interface orders to the HMI ECU. The HMI ECU uses a keypad and an LCD to interact with the user , take inputs and send user requests and passwors to the Control ECU. 

The door can be opened using a DC motor, and if the password is entered incorrectly three times in a row, a buzzer is triggered to indicate an unauthorized door opening attempt. This system provides an efficient and secure way to control access to a door.

# Simulation
https://github.com/My-GitHub99/Door-Locker-System/assets/121635850/c911feef-903d-440b-888e-7e03593a1903
