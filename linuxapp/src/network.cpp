#include "network.h"
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>

using namespace std;

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