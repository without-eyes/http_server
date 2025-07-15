#include "../../include/http_client.h"

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
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
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(8080);
    return serverAddress;
}

void connect_to_server(int fileDescriptor, struct sockaddr_in serverAddress) {
    if (connect(fileDescriptor, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr_in)) == -1) {
        perror("Could not connect to server");
        exit(EXIT_FAILURE);
    }
}

void send_request(int fileDescriptor, const char* request, size_t length) {
    if (send(fileDescriptor, request, length, 0) == -1) {
        perror("Could not send request");
    }
}

void receive_and_print_response(int fileDescriptor) {
    char response[512];
    ssize_t received = recv(fileDescriptor, &response, sizeof(response), 0);
    if (received == -1) {
        perror("Could not receive response");
        return;
    }
    response[received] = '\0';
    printf("%s", response);
}