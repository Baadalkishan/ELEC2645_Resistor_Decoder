# ELEC2645 Resistor Colour Code Decoder

## Overview
This project is a command line application written in C which decodes resistor color codes. This program supports both 4-band resistors and 5-band resistors, allowing users to input the resistor band colors one by one as text and recieve the corresponding resistance value and tolerance.

The application also stores the last decoded resistor using basic file input/output, which can be viewed later via the menu.

---


## Features
- Decode 4-band resistors
- Decode 5-band resistors
- Menu driven user interface
- Saves and displays the last decoded resistor
- Case insensitive inputs
- Displays resistance value and tolerance

---


## File Structure
- 'main.c'  -  Handles most of the user interface
- 'funcs.c' -  Implements resistor decoding logic and helper functions
- 'funcs.h' - Function declarations that are shared between the two source files
- 'last_resistor.txt' - Stores the most recent decoded resistor

---


## Build and Run Instructions

You can compile the program using  `gcc main.c funcs.c -o resistor_decoder `

Then run the program with `./resistor_decoder`


