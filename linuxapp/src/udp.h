#ifndef UDP_H
#define UDP_H

#include <bits/stdc++.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT 2000
#define MAXLINE 1024

int startUdpListener();

int receiveNextPacket(int sockfd, char result[MAXLINE]);

#endif
