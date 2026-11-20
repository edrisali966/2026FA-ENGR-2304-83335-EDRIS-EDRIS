
# ENGR 2304 - Programming Assignment P09

## Pressure Control and LED Countdown

**Student:** Edris Edris  
**Course:** ENGR 2304  
**College:** Dallas College  
**Semester:** Fall 2026

## Project Description

This project uses Arduino Uno and Tinkercad to simulate a pressure control system and an LED countdown.

The program reads the target pressure from potentiometer A0. It compares the target pressure with the current pressure.

When the current pressure is below the target, the program displays "Compressor ON" in the Serial Monitor.

When the target pressure is reached, the program displays "Compressor OFF" and starts a countdown using four LEDs.

## Components

- Arduino Uno
- Two potentiometers
- Four LEDs
- Resistors
- Breadboard
- Connecting wires

## Testing

The countdown was tested in Tinkercad.

The current code uses a fixed pressure value of 100 PSI in test mode. The A1 pressure input has not been fully verified.

To use the A1 input, change `testMode` to `false` and test the circuit again.

## Note

This project is for educational simulation only. It does not control a real compressor or rocket launcher.
