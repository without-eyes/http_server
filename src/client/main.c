#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../../include/http_client.h"

int main(void) {
    int fileDescriptor = create_file_descriptor();

    struct sockaddr_in serverAddress = create_server_address();
    connect_to_server(fileDescriptor, serverAddress);

    while (1) {
        char request[256]; // GET /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n
        printf("> ");
        fgets(request, sizeof(request), stdin);
        send_request(fileDescriptor, request, strlen(request));
        receive_and_print_response(fileDescriptor);
    }

    close(fileDescriptor);
    return 0;
}
