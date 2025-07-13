#include <stdio.h>
#include <stdlib.h>
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

    struct sockaddr_in peer_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    int client_socket = accept(fd, (struct sockaddr*)&peer_addr, &addr_len);

    size_t buff_len = 1024;
    char* buff = malloc(buff_len);
    ssize_t received = recv(client_socket, buff, buff_len, 0);
    buff[received] = '\0';

    printf("%s\n", buff);

    free(buff);
    close(fd);
    close(client_socket);
    return 0;
}