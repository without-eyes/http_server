#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <netinet/in.h>

int create_file_descriptor();

struct sockaddr_in create_server_address();

void bind_address_to_socket(int fileDescriptor, struct sockaddr_in serverAddress);

void handle_requests(int fileDescriptor);

void start_listening(int fileDescriptor);

int accept_connection(int fileDescriptor);

void receive_and_print_request(int clientSocket);

void send_response(int clientSocket);

char* get_html_page(const char* name);

#endif //HTTP_SERVER_H