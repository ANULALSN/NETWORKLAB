#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>  // Required for socket functions

#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[100];

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    // Receive the date and time from the server
    read(sockfd, buffer, sizeof(buffer));
    printf("Server date and time: %s\n", buffer);

    // Close the socket
    close(sockfd);
    return 0;
}
