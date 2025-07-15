#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <netinet/in.h>

int create_file_descriptor();

struct sockaddr_in create_server_address();

void connect_to_server(int fileDescriptor, struct sockaddr_in serverAddress);

char* send_request(int fileDescriptor, const char* request, size_t length);

void receive_and_print_response(int fileDescriptor);

#endif //HTTP_CLIENT_H