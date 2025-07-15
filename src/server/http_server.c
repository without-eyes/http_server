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
        int clientSocket = accept_connection(fileDescriptor);
        if (clientSocket == -1) break;

        receive_and_print_request(clientSocket);
        send_response(clientSocket);

        close(clientSocket);
    }
}

int accept_connection(int fileDescriptor) {
    struct sockaddr_in peerAddress;
    socklen_t addressLength = sizeof(struct sockaddr_in);
    int clientSocket = accept(fileDescriptor, (struct sockaddr*)&peerAddress, &addressLength);

    if (clientSocket == -1) {
        perror("Could not accept connection");
    }

    return clientSocket;
}

void receive_and_print_request(int clientSocket) {
    char request[512];
    ssize_t received = recv(clientSocket, request, sizeof(request), 0);
    request[received] = '\0';
    printf("%s", request);
}

void send_response(int clientSocket) {
    char* response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\nContent-Type: text/plain\r\n\r\nHello, world!\n";
    send(clientSocket, response, strlen(response), 0);
}