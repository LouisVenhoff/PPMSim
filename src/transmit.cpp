#include "transmit.h"
#include "ppmParser.h"
#include "axisCalc.h"
#include <Arduino.h>


TaskHandle_t ppmTaskHandle = NULL;

void sendSnapshot(long snapshot[CHANNELS]){
    //TODO: Send UDP Message to Address
    // Serial.println("Sending snapshot");

    

    // Serial.println();
    for(int i = 0; i < CHANNELS; i++){
        if(i != 1){
            continue;
        }

        Serial.println(snapshot[i]);
    }
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
