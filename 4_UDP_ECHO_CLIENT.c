#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    printf("Enter a string to send to the server: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character

    // Send data to server
    sendto(sockfd, (const char *)buffer, strlen(buffer), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Message sent to server: %s\n", buffer);

    // Receive echoed data from server
    int n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, 0, NULL, NULL);
    buffer[n] = '\0';  // Null-terminate the received data
    printf("Received from server: %s\n", buffer);

    close(sockfd);
    return 0;
}
