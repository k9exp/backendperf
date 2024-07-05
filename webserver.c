#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#define APP_MAX_BUFFER 1024
#define PORT 1999

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
    // SOCK_STREAM -> TCP
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

    // Creates the queues
    // Listen for clients, with 10 backlog (10 connection in accept queue)
    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    while(1){
        printf("\nWaiting for a connection...\n");

        // Accept a client connection
        if ((client_fd = accept(server_fd, (struct sockaddr*)&address,(socklen_t*)(&address_len))) < 0) {
             perror("Accpet failed");
             exit(EXIT_FAILURE);
        }

        // read data from OS receive buffer to the application (buffer)
        read(client_fd, buffer, APP_MAX_BUFFER);

        printf("%s\n", buffer);

        char *http_response = "HTTP/1.1 200 OK\r\n"
                              "Content-Type: text/plain\r\n"
                              "Content-Length: 12\r\n"
                              "\r\n"
                              "Hello World!";

        write(client_fd, http_response, strlen(http_response));

        close(client_fd);
    }


    return 0;
}

