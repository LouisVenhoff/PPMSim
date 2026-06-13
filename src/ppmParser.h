#ifndef ppmParser_H
#define ppmParser_H

#include <Arduino.h>

#define CHANNELS 8

uint16_t makeSnapshot();
void setupPPMParser(int ppmPin);

#endif