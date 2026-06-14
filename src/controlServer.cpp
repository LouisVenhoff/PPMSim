#include "controlServer.h"
#include "transmit.h"
#include <WebServer.h>
#include <ArduinoJson.h>


WebServer server(80);


void handleServerStart(){
    if(server.hasArg("plain")){
        String body = server.arg("plain");

        JsonDocument doc;

        deserializeJson(doc, body);

        const char* ip = doc["ip"];

        Serial.println(ip);

        startLiveTask();

        digitalWrite(ONBOARD_LED, 1);
        
        server.send(200);
    }
    else{
        Serial.println("No Valid Body!");

        server.send(400);
    }

}

void handleServerStop(){
    
    stopLiveTask();
    
    digitalWrite(ONBOARD_LED, 0);

    server.send(200);
}


void initializeServer(){

    pinMode(ONBOARD_LED, OUTPUT);

    server.on("/", HTTP_GET, []() {
        server.send(200, "text/plain", "ESP32 Webserver");
    });

    server.on("/start", HTTP_POST, handleServerStart);

    server.on("/stop", HTTP_POST, handleServerStop);

    
    server.begin();
    Serial.println("Server is listening!");

    while(1){
        server.handleClient();
    }

}