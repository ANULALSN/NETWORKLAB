#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void sendFrames(int start, int windowSize, int totalFrames);
int isFrameLost();

int main() {
    int windowSize, totalFrames;
    
    printf("Enter the total number of frames: ");
    scanf("%d", &totalFrames);
    
    printf("Enter the window size: ");
    scanf("%d", &windowSize);
    
    int base = 0;
    srand(time(NULL)); // Seed for random number generation

    while (base < totalFrames) {
        sendFrames(base, windowSize, totalFrames);
        int ack = base;

        for (int i = base; i < base + windowSize && i < totalFrames; i++) {
            if (isFrameLost()) {
                printf("Acknowledgment for Frame %d lost. Retransmitting window...\n", i);
                break;
            }
            ack++;
        }
        base = ack; // Slide the window
    }

    printf("All frames successfully transmitted!\n");
    return 0;
}

void sendFrames(int start, int windowSize, int totalFrames) {
    printf("Sending frames: ");
    for (int i = start; i < start + windowSize && i < totalFrames; i++) {
        printf("%d ", i);
    }
    printf("\n");
}

int isFrameLost() {
    return rand() % 5 == 0; // Simulate a random frame loss with 20% probability
}

