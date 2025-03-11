#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockdes, newsock;
    struct sockaddr_in server, client;
    char msg[2000], reply[2000];

    // Create socket
    sockdes = socket(AF_INET, SOCK_STREAM, 0);  // Create a TCP socket

    // Setup server details
    server.sin_family = AF_INET;           // Use IPv4
    server.sin_addr.s_addr = INADDR_ANY;   // Accept connections from any IP
    server.sin_port = htons(8888);         // Listen on port 8888

    // Bind socket to IP and port
    bind(sockdes, (struct sockaddr*)&server, sizeof(server));

    // Listen for incoming connections
    listen(sockdes, 3);  // Allow up to 3 pending connections

    // Accept incoming connection
    newsock = accept(sockdes, (struct sockaddr*)&client, (socklen_t*)&(int){sizeof(client)});

    // Communicate with client
    while (1) {
        memset(reply, 0, sizeof(reply));  // Clear the reply buffer
        recv(newsock, reply, sizeof(reply), 0);  // Receive data from client
        printf("From Client: %s\n", reply);      // Print client's message

        printf("To Client: ");
        scanf("%s", msg);                        // Get server's response
        send(newsock, msg, strlen(msg), 0);       // Send response to client
    }

    return 0;
}
