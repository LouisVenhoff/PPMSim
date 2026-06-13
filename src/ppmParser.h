#ifndef ppmParser_H
#define ppmParser_H

#include <Arduino.h>

#define CHANNELS 8

void makeSnapshot();
void setupPPMParser(int ppmPin);

#endif