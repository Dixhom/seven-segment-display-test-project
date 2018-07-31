# Seven-segment display test project

# What Is This?
A project to display a number on 4 [seven-segment displays](https://en.wikipedia.org/wiki/Seven-segment_display).

# Goal?
Given a number like 1.23, to display something like [ ][1].[2][3] on the seven-segment displays.

# Difficulty?
- Efficient wiring to save pins since connecting 4x7=28 electrodes of the displays to a microcontroller would use up all the pins.
- Good algorithm to convert a floating point number in a program to the flashing of each LED segment on the display. 

# Detail?
- Circuit diagram  
[circuit.png](circuit.png)

- Source code  
[7seg_test.ino](7seg_test.ino)  

- Result  
[movie.gif](movie.gif)