#include <Arduino.h>
#include "ppmParser.h"

#define PPM_PIN 23

void setup() {
  Serial.begin(9600);
  setupPPMParser(PPM_PIN);
}

void loop() {
  makeSnapshot();
  delay(100);
}
