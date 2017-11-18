# bow-clicker
An attachment for a bow to keep track of how many arrows have been shot.

This project uses an Atmel AVR atmega168P as the controller for the 4 digit 7 segment display that keeps track of the number of arrows shot

This project also uses my personal 'display lib' to write to a 7 segment display. 

# Planned additions

A capacitive switch which will be fired off when an arrow brushes by it. without having to manually click a button. (DONE)
Cap sensor has been added into circuit, One issue is that fletchings (feather) aren't conductive enough to fire off the sensor
so I need to put a piece of material on the arrow to cause the sensor to fire. 

# TODOs

- TODO: find out how to delete eeprom DONE 
- FIXME: 4th digit on display does not turn off DONE 
- TODO: get capacitance button working probably needs to implement PCI (pin change interrupt) DONE
- TODO: add 3rd button resetting state of the display back to 0
- TODO: rewire project to expose INT0 and INT1 for increase and decrease DONE
- TODO: integrate cap-sensor DONE
- TODO: Fix issue with starting number of display being [6535] (C's unsigned int maximum) DONE sort of..
