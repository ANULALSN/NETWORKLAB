#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockdes;
    struct sockaddr_in server;
    char msg[2000], reply[2000];

    // Create socket
    sockdes = socket(AF_INET, SOCK_STREAM, 0);  // Create a TCP socket

    // Setup server details
    server.sin_family = AF_INET;                // Use IPv4
    server.sin_port = htons(8888);              // Connect to port 8888
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  // Connect to localhost

    // Connect to server
    connect(sockdes, (struct sockaddr*)&server, sizeof(server));

    // Communicate with server
    while (1) {
        printf("To Server: ");
        scanf("%s", msg);                        // Get client's message
        send(sockdes, msg, strlen(msg), 0);      // Send message to server

        memset(reply, 0, sizeof(reply));        // Clear the reply buffer
        recv(sockdes, reply, sizeof(reply), 0);  // Receive server's response
        printf("From Server: %s\n", reply);     // Print server's response
    }

    return 0;
}
