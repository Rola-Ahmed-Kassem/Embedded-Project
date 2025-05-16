 CSE211s :INTRODUCTION TO EMBEDDED SYSTEMS
 
  Global Positioning System (GPS)
  
Project Description: 

The goal of this project is to develop an embedded system using C programming that 
gathers real-time positional coordinates while a microcontroller is in motion, and display 
location information on an attached computer or an LCD. The positioning system should 
use the TM4C123G LaunchPad. A map of the place with coordinates of various landmarks 
should be stored on the device. When approaching a landmark, its name should be 
displayed. 

Project Requirements: 

Hardware:

1. A microcontroller development board [tm4c123gh6pm]
2. A GPS module 
3. A personal computer (PC) 
4. Connecting cables (USB, serial, etc.)
   
Software: 
1. A C-development environment ( Keil 4)

Project Features:
1. After power-on, the system should read GPS module data and wait until there is 
a GPS fix . 
2. After acquiring the coordinates, it should display the name of closest landmark 
from a list of preset landmark coordinates. 
3. Periodically update the displayed location information.
