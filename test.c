#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Generic signal handler
void handle_signal(int sig) {
    printf("Received signal: %d\n", sig);
}

int main() {
    // Catch most common signals
    for (int i = 1; i < 32; i++) { // signals 1 to 31 are standard
        signal(i, handle_signal);
    }

    printf("Process PID: %d\n", getpid());
    printf("Waiting for signals (try Ctrl+C, Ctrl+\\)...\n");

    while (1) {
        pause(); // wait for any signal
    }

    return 0;
}
