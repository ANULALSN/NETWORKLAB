#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <errno.h>

int main() {
    int fd;
    struct ifreq ifr;
    char iface[] = "eno1";  // Change to your correct network interface name
    unsigned char *mac;

    // Open a socket to communicate with the kernel
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Set interface name
    strncpy(ifr.ifr_name, iface, IFNAMSIZ - 1);

    // Get the IP address
    ifr.ifr_addr.sa_family = AF_INET;
    if (ioctl(fd, SIOCGIFADDR, &ifr) == -1) {
        perror("ioctl SIOCGIFADDR failed");
        close(fd);
        return 1;
    }

    printf("IP Address: %s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

    // Get the MAC address
    if (ioctl(fd, SIOCGIFHWADDR, &ifr) == -1) {
        perror("ioctl SIOCGIFHWADDR failed");
        close(fd);
        return 1;
    }

    // Close the socket
    close(fd);

    mac = (unsigned char *)&ifr.ifr_hwaddr.sa_data;
    printf("MAC Address: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    return 0;
}

