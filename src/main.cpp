#include <Arduino.h>
#include "ppmParser.h"
#include "axisCalc.h"
#include "networkManager.h"
#include "controlServer.h"

#define PPM_PIN 23

void setup() {
  Serial.begin(9600);

  setupPPMParser(PPM_PIN);
  connect();
  initializeServer();


}

void loop() {

  

  // uint16_t snapshot[CHANNELS];

  // makeSnapshot(snapshot);

  // Serial.println("Aileron:");
  
  // for(int i = 0; i < CHANNELS; i++){
    
  //   if(i != 1){
  //     continue;
  //   }
    
  //   Serial.print(i);
  //   Serial.print(":");
  //   Serial.print(calculateAxisValue(snapshot[i]));
  //   Serial.println();
  // }

  // delay(100);
}
