#include "udp.h"

int startUdpListener(){
  int sockfd;
  struct sockaddr_in servaddr;

  if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
    std::cout << "UDP Socket creation failed" << std::endl;
    return -1;
  }

  memset(&servaddr, 0, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(2000);

  if(bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
    std::cout << "UDP Socket bind failed" << std::endl;
    return -1;
  }

  return sockfd;
}

int receiveNextPacket(int sockfd, char result[MAXLINE]){
  socklen_t len;
  int msgLength;
  char buffer[MAXLINE];
  struct sockaddr_in cliaddr;

  len = sizeof(cliaddr);

  memset(&cliaddr, 0, sizeof(cliaddr));

  msgLength = recvfrom(sockfd, (char* )buffer, MAXLINE, 0, ( struct sockaddr *) &cliaddr, &len);

  if(msgLength < 0){
    return msgLength;
  }

  buffer[msgLength] = '\0';

  memcpy(result, buffer, msgLength);

  result[msgLength] = '\0';

  return 1;
}