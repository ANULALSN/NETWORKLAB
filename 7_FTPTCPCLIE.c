#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    int sock, n;  // Declare 'n' here
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    FILE *file;

    // Create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Cannot create socket");
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);  // Server port
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {  // Server IP (localhost)
        perror("Invalid address/ Address not supported");
        close(sock);
        return 1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return 1;
    }

    printf("Connected to server.\n");

    // Get file name from user
    printf("Enter the file name to send: ");
    scanf("%s", buffer);

    // Send file name to server
    if (send(sock, buffer, strlen(buffer), 0) < 0) {
        perror("Send failed");
        close(sock);
        return 1;
    }

    // Open file for reading
    file = fopen(buffer, "rb");
    if (!file) {
        perror("File open failed");
        close(sock);
        return 1;
    }

    // Send file data
    while ((n = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (send(sock, buffer, n, 0) < 0) {
            perror("Send failed");
            fclose(file);
            close(sock);
            return 1;
        }
    }

    printf("File sent successfully.\n");

    // Close file and socket
    fclose(file);
    close(sock);

    return 0;
}
