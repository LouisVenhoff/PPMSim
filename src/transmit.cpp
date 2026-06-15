#include "transmit.h"
#include "ppmParser.h"
#include "axisCalc.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>

TaskHandle_t ppmTaskHandle = NULL;

WiFiUDP udp;

String targetIp;

uint16_t targetPort;

void sendSnapshot(long snapshot[CHANNELS]){
    //TODO: Send UDP Message to Address
    // Serial.println("Sending snapshot");

    JsonDocument doc;

    JsonArray channels = doc.to<JsonArray>();

    // Serial.println();
    for(int i = 0; i < CHANNELS; i++){
        channels.add(snapshot[i]);
    }

    String parsedJson;

    serializeJson(doc, parsedJson);

    udp.beginPacket(targetIp.c_str(), targetPort);
    udp.print(parsedJson);
    udp.endPacket();

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

        delay(1);
    }
}

void ppmReaderTask(void *parameter){
    startPPMReader();
}

void startLiveTask(String ip){
    if(ppmTaskHandle != NULL){
        return;
    };

    targetIp = ip;
    targetPort = 2000;
    
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
