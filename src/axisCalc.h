#ifndef axisCalc_H
#define axisCalc_H

#include <Arduino.h>

#define MIN_PPM 1100 //Remote axis at smallest position
#define MAX_PPM 1900 //Remote axis at highest position

#define MIN_HID -32768 //HID Joystick at smallest position
#define MAX_HID 32767  //HID Joystick at highest position

long calculateAxisValue(uint16_t ppmValue);

#endif