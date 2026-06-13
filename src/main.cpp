#include <Arduino.h>

#define PPM_PIN 23
#define CHANNELS 8

volatile uint16_t ppmValues[CHANNELS];
volatile uint8_t channelIndex = 0;

volatile unsigned long lastTime = 0;

uint16_t snapshottedValues[CHANNELS];

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

void makeSnapshot(){
  noInterrupts();

  for(int i = 0; i < CHANNELS; i++){
    snapshottedValues[i] = ppmValues[i];
  };

  interrupts();

  for(int j = 0; j < CHANNELS; j++){
    
    int currentChannel = j + 1;
    String result = "CH" + String(currentChannel) +  String(snapshottedValues[j]);
    
    if(currentChannel == 1){
      Serial.println(snapshottedValues[j]);
    }
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(PPM_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(PPM_PIN), ppmInterrupt, RISING);
}

void loop() {
  makeSnapshot();
  delay(100);
}
