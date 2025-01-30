#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockdes, n;
    struct sockaddr_in server, client;
    char msg[2000], reply[2000];
    socklen_t c;

    // Create socket
    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind socket
    if (bind(sockdes, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        return 1;
    }

    printf("Bind done. Waiting for data...\n");

    c = sizeof(client);

    // Receive message from client
    n = recvfrom(sockdes, msg, sizeof(msg) - 1, 0, (struct sockaddr *)&client, &c);
    if (n < 0) {
        perror("Receive failed");
        return 1;
    }
    msg[n] = '\0';  // Null-terminate received message

    printf("From client: %s\n", msg);

    // Get reply from server user
    printf("Enter reply: ");
    scanf("%s", reply);

    // Send reply to client
    if (sendto(sockdes, reply, strlen(reply), 0, (struct sockaddr *)&client, c) < 0) {
        perror("Send failed");
        return 1;
    }

    printf("Reply sent.\n");

    // Close socket
    close(sockdes);
    
    return 0;
}

