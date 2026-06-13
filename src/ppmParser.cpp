#include <cstdint>

#define PPM_PIN 23
#define CHANNELS 8

volatile uint16_t ppmValues[CHANNELS];
volatile uint8_t channelIndex = 0;

volatile unsigned long lastTime = 0;

uint16_t snapshottedValues[CHANNELS];

