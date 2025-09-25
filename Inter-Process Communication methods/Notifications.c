#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void handle_sigint(int sig) {
    printf("\nNotification received: SIGINT (Ctrl+C pressed)\n");
    exit(0);
}

int main() {
    // Step 1: Register signal handler
    signal(SIGINT, handle_sigint);

    printf("Program running. Press Ctrl+C to trigger notification...\n");

    // Step 2: Keep process running
    while(1) {
        printf("Waiting for notification...\n");
        sleep(2); // Sleep to simulate work
    }

    return 0;
}

