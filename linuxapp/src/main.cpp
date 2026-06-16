#include <iostream>
#include <string>

using namespace std;

string promptDeviceIp(){
   
    cout << "Enter IP Address of the DX6Sim Device (ESP32): ";

    string address;

    cin >> address;

   return address.c_str();
}

int main(){
    
    string deviceIP = promptDeviceIp();

    cout << deviceIP;

    return 0;
};


