#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockdes;
    struct sockaddr_in server;
    char msg[2000], reply[2000];

    sockdes = socket(AF_INET, SOCK_DGRAM, 0);  // Create UDP socket
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);  // Server port
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);  // Server IP (localhost)

    printf("Enter a message: ");
    scanf("%s", msg);  // Get message from user
    sendto(sockdes, msg, strlen(msg), 0, (struct sockaddr *)&server, sizeof(server));  // Send to server
    recvfrom(sockdes, reply, sizeof(reply), 0, NULL, NULL);  // Receive reply
    printf("From server: %s\n", reply);  // Print reply

    close(sockdes);  // Close socket
    return 0;
}
