#include <iostream>
#include <string>
#include "network.h"
#include <netinet/in.h>
using namespace std;

string promptDeviceIp(){
   
    cout << "Enter IP Address of the DX6Sim Device (ESP32): ";

    string address;

    cin >> address;

   return address;
}

int main(){
    
    setupRemoteConnection();
    
    return 0;
};


