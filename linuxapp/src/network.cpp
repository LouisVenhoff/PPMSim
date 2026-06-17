#include "network.h"
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>


using namespace std;
using json = nlohmann::json;

int getLocalIp(char * buffer, size_t bufferSize){
    struct ifaddrs *ifaddr, *ifa; 

    getifaddrs(&ifaddr);

    if (getifaddrs(&ifaddr) == -1) {
        return 1;
    }

    for(ifa = ifaddr; ifa != nullptr; ifa=ifa->ifa_next){

        if(ifa->ifa_addr == nullptr){
            continue;
        }

        if(ifa->ifa_addr->sa_family == AF_INET){
            struct sockaddr_in* addr = (struct sockaddr_in *)ifa->ifa_addr; 

            inet_ntop(AF_INET, &addr->sin_addr, buffer, bufferSize);

            if (strcmp(buffer, "127.0.0.1") != 0) {
                freeifaddrs(ifaddr);
                return 0;
            }
        }
    }
    freeifaddrs(ifaddr);
    return 1;
};



int setupRemoteConnection(){
    cout << "Enter IP Address of the DX6Sim Device (ESP32): ";

    std:string address;

    cin >> address;

    string url = "http://" + address + "/start";

    char localIp[INET_ADDRSTRLEN];

    int localIpResult = getLocalIp(localIp, sizeof(localIp));

    if(localIpResult > 0){
        cout << "Error while retrieving local IP Address!";
        return 1;
    }
    
    json body;
    body["ip"] = localIp;

    cout << "Connecting...";

    cpr::Response result = cpr::Post(
        cpr::Url{url},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{body.dump()}
    );

    return 0;
};