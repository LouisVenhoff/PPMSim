#ifndef ppmParser_H
#define ppmParser_H

#include <Arduino.h>

#define CHANNELS 6

void makeSnapshot(uint16_t output[CHANNELS]);
void setupPPMParser(int ppmPin);

#endif