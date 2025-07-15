#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <netinet/in.h>

int create_file_descriptor();

struct sockaddr_in create_server_address();

void bind_address_to_socket(int fileDescriptor, struct sockaddr_in serverAddress);

void handle_requests(int fileDescriptor);

#endif //HTTP_SERVER_H