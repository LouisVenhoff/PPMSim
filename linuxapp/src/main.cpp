#include <iostream>
#include <string>
#include <netinet/in.h>
#include "network.h"
#include "udp.h"

using namespace std;

string promptDeviceIp(){
   
    cout << "Enter IP Address of the DX6Sim Device (ESP32): ";

    string address;

    cin >> address;

   return address;
}

int main(){
    
    setupRemoteConnection();
    
    int fd = startUdpListener();
  
    if(fd < 0){
        cout << "Error while starting UDP Listener!";
    }
    
    
    while(true){
        char responseBuffer[1024];
        int msgLength = receiveNextPacket(fd, responseBuffer);

        cout << responseBuffer<< std::endl;
    }

    
    return 0;
};


