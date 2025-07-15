#include <netinet/in.h>
#include<unistd.h>
#include "../../include/http_server.h"

int main(void) {
    int fileDescriptor = create_file_descriptor();

    struct sockaddr_in serverAddress = create_server_address();
    bind_address_to_socket(fileDescriptor, serverAddress);

    handle_requests(fileDescriptor);

    close(fileDescriptor);
    return 0;
}
