#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAXLEN 1000

int main(int argc, char **argv) {
  int sockfd;
  struct sockaddr_in servaddr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(atoi(argv[2]));
  inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
  connect(sockfd, (struct servaddr *)&servaddr, sizeof(servaddr));
  char sendline[MAXLEN], recvline[MAXLEN];
  for (;;) {
    bzero(sendline, MAXLEN);
    bzero(recvline, MAXLEN);
    fgets(sendline, MAXLEN, stdin);
    write(sockfd, sendline, strlen(sendline));
    read(sockfd, recvline, strlen(sendline));
    fputs(recvline, stdout);
  }
  return 0;
}
