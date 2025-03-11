#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockdes;
    struct sockaddr_in server, client;
    char msg[2000], reply[2000];
    socklen_t c = sizeof(client);

    sockdes = socket(AF_INET, SOCK_DGRAM, 0);  // Create UDP socket
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);  // Bind to port 8888
    bind(sockdes, (struct sockaddr *)&server, sizeof(server));  // Bind socket

    recvfrom(sockdes, msg, sizeof(msg), 0, (struct sockaddr *)&client, &c);  // Receive message
    printf("From client: %s\n", msg);  // Print message

    printf("Enter reply: ");
    scanf("%s", reply);  // Get reply from user
    sendto(sockdes, reply, strlen(reply), 0, (struct sockaddr *)&client, c);  // Send reply

    close(sockdes);  // Close socket
    return 0;
}
