# SEELE_ArduinoDrumMachine
drum machine sequencer for arduino with i2c lcd display and EEPROM for storing sequences. uses pushbuttons to set options. hardware is pretty self explanatory but when the project is more developed ill have better documentation

there are a few menus displayed on the 2x16 LCD screen:

0 . sequence editor. use up down left right to edit the sequence of 10 selectable sounds.

1 . sequence select menu, select between 4 sequences stored in EEPROM

2 . "osc editor" menu, where paramters of synth can be edited

3 . EEPROM menu for saving sequences

4 . time menu for setting sequence playback speed, tempo clock pulse width (sound hold length)

5 . info menu displays info about device


## hardware

requires generic i2c LCD display with two lines of text

## software requirements

requires ```LiquidCrystal_I2C``` library. uses ```EEPROM``` library and ```wire``` library.

## notes

i made this before i knew what interrupts were, so the timing is very sluggish especially when editing sequences. i will be improving the code more now that i recovered it from an old hard drive that i had laying around i had lost the code for it.
