#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockdes;
    struct sockaddr_in server;
    char msg[2000], reply[2000];
    socklen_t server_len = sizeof(server);

    // Create UDP socket
    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes == -1) {
        perror("Cannot create socket");
        return 1;
    }

    // Configure server address
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);  // Server port
    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0) {  // Server IP (localhost)
        perror("Invalid address/ Address not supported");
        close(sockdes);
        return 1;
    }

    // Get message from user
    printf("Enter a message: ");
    scanf("%s", msg);

    // Send message to server
    if (sendto(sockdes, msg, strlen(msg), 0, (struct sockaddr *)&server, server_len) < 0) {
        perror("Send failed");
        close(sockdes);
        return 1;
    }

    // Receive reply from server
    if (recvfrom(sockdes, reply, sizeof(reply), 0, (struct sockaddr *)&server, &server_len) < 0) {
        perror("Receive failed");
        close(sockdes);
        return 1;
    }

    // Print the server's reply
    printf("From server: %s\n", reply);

    // Close the socket
    close(sockdes);
    return 0;
}
