#include "../../include/http_client.h"

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int create_file_descriptor() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

struct sockaddr_in create_server_address() {
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(8080);
    return serverAddress;
}

void connect_to_server(int fileDescriptor, struct sockaddr_in serverAddress) {
    connect(fileDescriptor, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr_in));
}

char* send_request(int fileDescriptor, const char* request, size_t length) {
    send(fileDescriptor, request, length, 0);
}

void receive_and_print_response(int fileDescriptor) {
    char response[512];
    ssize_t received = recv(fileDescriptor, &response, sizeof(response), 0);
    response[received] = '\0';
    printf("%s", response);
}