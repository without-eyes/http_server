#include "../../include/http_server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

int create_file_descriptor() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

struct sockaddr_in create_server_address() {
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);
    return serverAddress;
}

void bind_address_to_socket(int fileDescriptor, struct sockaddr_in serverAddress) {
    bind(fileDescriptor, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr_in));
}

void handle_requests(int fileDescriptor) {
    listen(fileDescriptor, SOMAXCONN);

    while (1) {
        struct sockaddr_in peer_addr;
        socklen_t addr_len = sizeof(struct sockaddr_in);
        int client_socket = accept(fileDescriptor, (struct sockaddr*)&peer_addr, &addr_len);

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
}