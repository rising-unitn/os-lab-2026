#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static pid_t child_pid;

void alarm_handler(int signum) {
    (void)signum;
    printf("Parent: SIGALRM received. Sending SIGTERM to child %d\n",
           child_pid);
    kill(child_pid, SIGTERM);
}

int main() {
    child_pid = fork();
    if (child_pid < 0) {
        perror("fork");
        return 1;
    }
    if (child_pid == 0) {
        /* child */
        while (1) {
            printf("Child alive (PID: %d)\n", getpid());
            sleep(1);
        }
    }

/* parent */
    struct sigaction act;
    act.sa_handler = alarm_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, NULL);

    alarm(5);
    printf("Parent: alarm set for 5 seconds.\n");
    wait(NULL);
    printf("Parent: child terminated. Exiting.\n");
    return 0;
}
