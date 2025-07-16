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

        char* request = receive_request(clientSocket);
        struct Request parsedRequest = parse_request(request);

        send_response(clientSocket, parsedRequest);

        free(request);
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

char* receive_request(int clientSocket) {
    char* request = malloc(256);
    ssize_t received = recv(clientSocket, request, 256, 0);
    if (received == -1) {
        perror("Could not receive request");
        return NULL;
    }
    request[received] = '\0';
    return request;
}

void send_response(int clientSocket, struct Request parsedRequest) {
    if (strcmp(parsedRequest.method, "GET") != 0) {
        return;
    }

    char* page = get_html_page(parsedRequest.path);
    size_t responseLength = strlen(page) + 256;
    char* response = malloc(responseLength);
    snprintf(response, responseLength, "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nContent-Type: text/plain\r\n\r\n%s\n", strlen(page), page);
    if (send(clientSocket, response, strlen(response), 0) == -1) {
        perror("Could not send response");
    }
    free(page);
    free(response);
}

char* get_html_page(const char* name) {
    char path[256];
    snprintf(path, sizeof(path), "./html%s", name);
    FILE* file = fopen(path, "r");

    if (file == NULL) {
        perror("Could not open file");
        // send 404
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    const size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = malloc(length + 1);
    fread(content, 1, length, file);
    content[length] = '\0';

    fclose(file);
    return content;
}

struct Request parse_request(char* request) {
    if (request == NULL) {
        perror("Could not parse request");
        exit(EXIT_FAILURE);
    }

    struct Request parsedRequest;

    char* field = strtok(request, " ");
    parsedRequest.method = field;

    field = strtok(NULL, " ");
    parsedRequest.path = field;

    field = strtok(NULL, " ");
    parsedRequest.htmlVersion = field;\

    return parsedRequest;
}