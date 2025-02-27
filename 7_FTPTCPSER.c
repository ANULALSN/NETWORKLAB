#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    int server_sock, client_sock, n;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    FILE *file;

    // Create TCP socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8888);

    // Bind socket
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_sock);
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_sock, 1) < 0) {
        perror("Listen failed");
        close(server_sock);
        return 1;
    }

    printf("Server listening on port 8888...\n");

    // Accept a client connection
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
    if (client_sock < 0) {
        perror("Accept failed");
        close(server_sock);
        return 1;
    }

    printf("Client connected.\n");

    // Receive file name from client
    n = recv(client_sock, buffer, BUFFER_SIZE, 0);
    if (n < 0) {
        perror("Receive failed");
        close(client_sock);
        close(server_sock);
        return 1;
    }
    buffer[n] = '\0';  // Null-terminate the file name

    printf("Receiving file: %s\n", buffer);

    // Open file for writing
    file = fopen(buffer, "wb");
    if (!file) {
        perror("File open failed");
        close(client_sock);
        close(server_sock);
        return 1;
    }

    // Receive file data
    while ((n = recv(client_sock, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, n, file);
    }

    if (n < 0) {
        perror("Receive failed");
    }

    printf("File received successfully.\n");

    // Close file and sockets
    fclose(file);
    close(client_sock);
    close(server_sock);

    return 0;
}
