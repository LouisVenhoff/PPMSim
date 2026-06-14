#include <WiFi.h>
#include <EEPROM.h>
#include <WiFiManager.h>
#include "networkManager.h"

WiFiManager wm;


char ssid[32];
char pwd[32];

bool shouldSaveConfig = false;



void saveConfigCallback(){
    shouldSaveConfig = true;
}

void saveCredentials(const char* newSSID, const char* newPwd){
    for(int i = 0; i < 32; i++){
        EEPROM.write(0 + i, newSSID[i]);
    }

    for(int i = 0; i < 32; i++){
        EEPROM.write(100 + i, newPwd[i]);
    }

    EEPROM.write(200, 1);

    EEPROM.commit();

    Serial.println("Written data to EEPROM");
}

void resetSavedFlag(){
    EEPROM.write(200, 0);

    EEPROM.commit();
}

bool checkCredentialsConfigured(){
    int configured = EEPROM.read(200);
    Serial.println("Configuredvalue: " + configured);
    return configured == 1;
}

void readCredentials(){
    for(int i = 0; i < 32; i++){
        ssid[i] = EEPROM.read(0 + i);
    }

    ssid[31] = '\0';

    for(int i = 0; i < 32; i++){
        pwd[i] = EEPROM.read(100 + i);
    }

    pwd[31] = '\0';

    delay(5000);
}

void resetNT(){
    EEPROM.write(200, 0);
    EEPROM.commit();
}

void initialize(){

    pinMode(RESET_NT_BUTTON, INPUT);

    attachInterrupt(digitalPinToInterrupt(RESET_NT_BUTTON), resetNT, RISING);

    EEPROM.begin(512);

    wm.setSaveConfigCallback(saveConfigCallback);

    if(!checkCredentialsConfigured()){
        wm.startConfigPortal("SimBoxConfig");

        if(shouldSaveConfig){
            saveCredentials(wm.getWiFiSSID().c_str(), wm.getWiFiPass().c_str());
            ESP.restart();
        }
    }
    else{
        readCredentials();
    }

}

int connect(){
    
    initialize();

    pinMode(ONBOARD_LED, OUTPUT);

    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid, pwd);

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    digitalWrite(ONBOARD_LED, HIGH);

    delay(2000);

    digitalWrite(ONBOARD_LED, LOW);

    return 1;
}