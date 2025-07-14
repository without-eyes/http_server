#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(void) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8080);

    connect(fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in));

    char buff[64] = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";
    send(fd, buff, sizeof(buff), 0);

    char* response = malloc(1024);
    int recieved = recv(fd, response, 1024, 0);
    response[recieved] = '\0';
    printf("%s", response);

    free(response);
    close(fd);
    return 0;
}