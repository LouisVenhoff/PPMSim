#include "ppmParser.h"

volatile uint16_t ppmValues[CHANNELS];
volatile uint8_t channelIndex = 0;

volatile unsigned long lastTime = 0;

void ppmInterrupt(){

  unsigned long currentTime = micros();

  unsigned long pulseLength = currentTime - lastTime;

  lastTime = currentTime;

  if(pulseLength > 3000){
    channelIndex = 0;
  }
  else{
    if(channelIndex < CHANNELS){
      ppmValues[channelIndex] = pulseLength;
      channelIndex++;
    }
  }
}

void makeSnapshot(uint16_t output[CHANNELS]){
  noInterrupts();

  for(int i = 0; i < CHANNELS; i++){
    output[i] = ppmValues[i];
  }

  interrupts();
}

void setupPPMParser(int ppmPin){
    pinMode(ppmPin, INPUT);

    attachInterrupt(digitalPinToInterrupt(ppmPin), ppmInterrupt, RISING);
}

