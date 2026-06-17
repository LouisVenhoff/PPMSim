#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <cstddef>

int getLocalIp(char* buffer, size_t bufferSize);
int setupRemoteConnection();

#endif 