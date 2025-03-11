#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket
    struct sockaddr_in server_addr = {.sin_family = AF_INET, .sin_port = htons(PORT), .sin_addr.s_addr = inet_addr("127.0.0.1")};
    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)); // Connect to the server

    char buffer[100];
    read(sockfd, buffer, sizeof(buffer)); // Receive time from server
    printf("Server date and time: %s\n", buffer);

    close(sockfd); // Close the socket
    return 0;
}
