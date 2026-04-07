#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum) {
    printf("\nSIGINT delivered! (signal %d)\n", signum);
}

int main() {
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);

    sigset_t set, pending;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_BLOCK, &set, NULL);

    printf("SIGINT is now blocked. Press Ctrl+C -- nothing will happen for 5 seconds.\n");
    sleep(5);

sigpending(&pending);
    if (sigismember(&pending, SIGINT)) {
        printf("SIGINT was pending! Unblocking now...\n");
    } else {
        printf("No pending SIGINT. Continuing normally.\n");
    }

    sigprocmask(SIG_UNBLOCK, &set, NULL);
    /* If SIGINT was pending, handler runs here */

    printf("Program finished.\n");
    return 0;
}
