#include <iostream>
#include <string>
#include <netinet/in.h>
#include "network.h"
#include "udp.h"
#include "virtualDevice.h"

using namespace std;

string promptDeviceIp(){
   
    cout << "Enter IP Address of the DX6Sim Device (ESP32): ";

    string address;

    cin >> address;

   return address;
}

int main(){
    
    setupRemoteConnection();

    virtualDeviceInit();
    int fd = startUdpListener();
  
    if(fd < 0){
        cout << "Error while starting UDP Listener!";
    }
    
    
    while(true){
        char responseBuffer[1024];
        int msgLength = receiveNextPacket(fd, responseBuffer);
        //cout << "Received packet with length: " << responseBuffer << std::endl;
        virtualDeviceUpdate(responseBuffer);
    }

    
    return 0;
};


