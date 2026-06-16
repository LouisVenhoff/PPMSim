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
    
    string deviceIP = promptDeviceIp();

    char localIp[INET_ADDRSTRLEN];

    int test = getLocalIp(localIp, sizeof(localIp));

    if(test == 0){
        cout << localIp;
    }
    else{
        cout << "Error while loading local ip address";
    }

    return 0;
};


