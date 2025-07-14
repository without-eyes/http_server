#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<unistd.h>

int main(void) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(8080);

    bind(fd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr_in));

    listen(fd, SOMAXCONN);

    while (1) {
        struct sockaddr_in peer_addr;
        socklen_t addr_len = sizeof(struct sockaddr_in);
        int client_socket = accept(fd, (struct sockaddr*)&peer_addr, &addr_len);

        size_t buff_len = 1024;
        char* buff = malloc(buff_len);
        ssize_t received = recv(client_socket, buff, buff_len, 0);
        buff[received] = '\0';

        printf("%s\n", buff);

        char* response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\nContent-Type: text/plain\r\n\r\nHello, world!\n";
        send(client_socket, response, strlen(response), 0);

        free(buff);
        close(client_socket);
    }

    close(fd);
    return 0;
}