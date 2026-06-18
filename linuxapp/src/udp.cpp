int startUdpListener(){
  int sockfd;
  char buffer[1024];
  struct sockaddr_in servaddr, cliaddr;

  if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
    std::cout << "UDP Socket creation failed" << std::endl;
    return -1;
  }

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(2000);

  if(bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
    std::cout << "UDP Socket bind failed" << std::endl;
    return -1;
  }

  socklen_t len;
  int n;

  len = sizeof(cliaddr);

  n = recvfrom(sockfd, (char* )buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
  buffer[n] = '\0';
  printf(buffer);

}