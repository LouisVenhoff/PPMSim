#include "axisCalc.h"

long calculateAxisValue(uint16_t ppmValue){
    long hidRange = MAX_HID - MIN_HID;
    long ppmRange = MAX_PPM - MIN_PPM;

    long result = (ppmValue - MIN_PPM) * (hidRange) / (ppmRange) + MIN_HID;

    return result;
}