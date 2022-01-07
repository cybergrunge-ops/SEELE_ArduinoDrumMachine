# SEELE_ArduinoDrumMachine
drum machine sequencer for arduino with i2c lcd display and EEPROM for storing sequences

## hardware

requires generic i2c LCD display with two lines of text

## software requirements

requires ```LiquidCrystal_I2C``` library. uses ```EEPROM``` library and ```wire``` library.

## notes

i made this before i knew what interrupts were, so the timing is very sluggish especially when editing sequences. i will be improving the code more now that i recovered it from an old hard drive that i had laying around i had lost the code for it.
