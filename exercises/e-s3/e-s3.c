#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum) {
    if (signum == SIGUSR1)
        printf("Hello from SIGUSR1\n");
    else if (signum == SIGUSR2)
        printf("Hello from SIGUSR2\n");
}

int main() {
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);

    printf("PID: %d. Waiting for SIGUSR1 or SIGUSR2...\n", getpid());
    while (1)
        pause();

    return 0;
}
