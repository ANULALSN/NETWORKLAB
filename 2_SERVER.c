#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockdes, newsock, c;
    struct sockaddr_in server, client;
    char msg[2000], reply[2000];
    
    // Create socket
    sockdes = socket(AF_INET, SOCK_STREAM, 0);
    if (sockdes == -1) {
        printf("\nCannot create socket\n");
        return 1;
    }
    
    // Setup server details
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);
    
    // Bind socket to IP and port
    if (bind(sockdes, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Bind Failed\n");
        return 1;
    }
    printf("\nBind done\n");
    
    // Listen for incoming connections
    listen(sockdes, 3);
    printf("\nWaiting for incoming connection...\n");
    c = sizeof(struct sockaddr_in);
    
    // Accept incoming connection
    newsock = accept(sockdes, (struct sockaddr*)&client, (socklen_t*)&c);
    if (newsock == -1) {
        perror("\nAccept Failed\n");
        return 1;
    }
    printf("\nConnection accepted\n");
    
    // Communicate with client
    while (1) {
        memset(reply, 0, sizeof(reply));  // Clear buffer
        recv(newsock, reply, sizeof(reply), 0);
        printf("\nFrom Client:\n");
        puts(reply);
        
        printf("\nTo Client:\n");
        scanf("%s", msg);
        send(newsock, msg, strlen(msg), 0);
    }
    
    return 0;
}

