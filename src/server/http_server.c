#include "../../include/http_server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

int create_file_descriptor() {
    int fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (fileDescriptor == -1) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    return fileDescriptor;
}

struct sockaddr_in create_server_address() {
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);
    return serverAddress;
}

void bind_address_to_socket(int fileDescriptor, struct sockaddr_in serverAddress) {
    if (bind(fileDescriptor, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr_in)) == -1) {
        perror("Could not bind server address to file descriptor");
        exit(EXIT_FAILURE);
    }
}

void handle_requests(int fileDescriptor) {
    start_listening(fileDescriptor);

    while (1) {
        int clientSocket = accept_connection(fileDescriptor);
        if (clientSocket == -1) break;

        receive_and_print_request(clientSocket);
        send_response(clientSocket);

        close(clientSocket);
    }
}

void start_listening(int fileDescriptor) {
    int result = listen(fileDescriptor, SOMAXCONN);
    if (result == -1) {
        perror("Could not listen on socket");
        exit(EXIT_FAILURE);
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
    if (received == -1) {
        perror("Could not receive request");
        return;
    }
    request[received] = '\0';
    printf("%s", request);
}

void send_response(int clientSocket) {
    char* response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\nContent-Type: text/plain\r\n\r\nHello, world!\n";
    if (send(clientSocket, response, strlen(response), 0) == -1) {
        perror("Could not send response");
    }
}