#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_socklen_t.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLEN 1000

int main(int argc, char **argv) {
  int listenfd, connfd;
  struct sockaddr_in servaddr, cliaddr;
  socklen_t clilen;
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(atoi(argv[1]));
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  listen(listenfd, 10);
  clilen = sizeof(cliaddr);
  connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
  for (;;) {
    ssize_t n;
    char buff[MAXLEN];
    bzero(buff, MAXLEN);
    n = read(connfd, buff, MAXLEN);
    write(connfd, buff, n);
  }
  return 0;
}
