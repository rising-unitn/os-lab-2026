#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static volatile int counter = 0;
static volatile int running = 1;

void handle_sigusr1(int signum) {
    (void)signum;
    counter++;
    printf("Received SIGUSR1: Incrementing counter.\n");
}

void handle_sigusr2(int signum) {
    (void)signum;
    printf("Received SIGUSR2: Printing counter value: %d\n", counter);
    counter = 0;
}

void handle_sigterm(int signum) {
    (void)signum;
    printf("Received SIGTERM: Exiting gracefully. Final counter value: %d\n",
           counter);
    running = 0;
}

int main(void) {
    struct sigaction sa_usr1, sa_usr2, sa_term;

    sa_usr1.sa_handler = handle_sigusr1;
    sigemptyset(&sa_usr1.sa_mask);
    sa_usr1.sa_flags = 0;
    sigaction(SIGUSR1, &sa_usr1, NULL);

    sa_usr2.sa_handler = handle_sigusr2;
    sigemptyset(&sa_usr2.sa_mask);
    sa_usr2.sa_flags = 0;
    sigaction(SIGUSR2, &sa_usr2, NULL);

sa_term.sa_handler = handle_sigterm;
    sigemptyset(&sa_term.sa_mask);
    sa_term.sa_flags = 0;
    sigaction(SIGTERM, &sa_term, NULL);

    printf("PID: %d\n", getpid());

    while (running) {
        printf("Working...\n");
        sleep(2);
    }
    return 0;
}
