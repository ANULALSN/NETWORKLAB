#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket
    struct sockaddr_in server_addr = {.sin_family = AF_INET, .sin_port = htons(PORT), .sin_addr.s_addr = INADDR_ANY};
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)); // Bind socket to port 8080
    listen(server_fd, 1); // Listen for incoming connections
    printf("Daytime server is listening on port %d...\n", PORT);

    while (1) {
        int new_socket = accept(server_fd, NULL, NULL); // Accept a new connection
        time_t rawtime = time(NULL); // Get current time
        char buffer[100];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&rawtime)); // Format time
        write(new_socket, buffer, sizeof(buffer)); // Send time to client
        close(new_socket); // Close the connection
    }
}
