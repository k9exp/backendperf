#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define APP_MAX_BUFFER 1024
#define PORT 8080

int main(){
    // Server and Client File Descriptors
    int server_fd, client_fd;

    // socked address
    struct sockaddr_in address;
    int address_len = sizeof(address);

    // Buffer array to store client data 
    // copy data from kernel 
    char buffer[APP_MAX_BUFFER] = {0};

    // Server Socked
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socked creating failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET; // IPv4
    address.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
    address.sin_port = htons(PORT);

    if (bind(server_fd, (const struct sockaddr*) &address, address_len) < 0) {
        perror("Faild to bind socked and address");
        exit(EXIT_FAILURE);
    }


    return 0;
}
