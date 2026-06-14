#include "transmit.h"
#include "ppmParser.h"
#include "axisCalc.h"
#include <Arduino.h>
#include <ArduinoJson.h>

TaskHandle_t ppmTaskHandle = NULL;

void sendSnapshot(long snapshot[CHANNELS]){
    //TODO: Send UDP Message to Address
    // Serial.println("Sending snapshot");

    JsonDocument doc;

    JsonArray channels = doc.to<JsonArray>();

    // Serial.println();
    for(int i = 0; i < CHANNELS; i++){
        channels.add(snapshot[i]);
    }

    serializeJson(doc, Serial);
    Serial.println();
}

void doSomesthing(){
    Serial.print("HIHI");
}

void startPPMReader(){
    while(1){
        uint16_t snapshot[CHANNELS];

        long axisMappedSnapshot[CHANNELS];
    
        makeSnapshot(snapshot);

        for(int i = 0; i < CHANNELS; i++){
            axisMappedSnapshot[i] = calculateAxisValue(snapshot[i]);
        }

        sendSnapshot(axisMappedSnapshot);

        delay(10);
    }
}

void ppmReaderTask(void *parameter){
    startPPMReader();
}

void startLiveTask(){
    if(ppmTaskHandle != NULL){
        return;
    };
    
    xTaskCreate(
        ppmReaderTask,
        "PPMReader",
        4096,
        NULL,
        1,
        &ppmTaskHandle
    );
}

void stopLiveTask(){
    if(ppmTaskHandle != NULL){
        vTaskDelete(ppmTaskHandle);
        ppmTaskHandle = NULL;
    }
}
