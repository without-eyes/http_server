#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <netinet/in.h>

struct Request {
    char* method;
    char* path;
    char* htmlVersion;
};

int create_file_descriptor();

struct sockaddr_in create_server_address();

void bind_address_to_socket(int fileDescriptor, struct sockaddr_in serverAddress);

void handle_requests(int fileDescriptor);

void start_listening(int fileDescriptor);

int accept_connection(int fileDescriptor);

char* receive_request(int clientSocket);

void send_response(int clientSocket, struct Request parsedRequest);

char* get_html_page(const char* name);

struct Request parse_request(char* request);

void print_connected_client_ip(struct sockaddr_in address);

void handle_client(int clientSocket);

#endif //HTTP_SERVER_H