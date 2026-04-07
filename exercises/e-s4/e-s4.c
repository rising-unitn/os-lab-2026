#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static pid_t child1, child2;

void parent_handler(int signum) {
    (void)signum;
    printf("Parent: received SIGUSR2. Starting orchestration.\n");

    sleep(3);
    printf("Parent: suspending child %d\n", child1);
    kill(child1, SIGSTOP);
    sleep(3);
    printf("Parent: resuming child %d\n", child1);
    kill(child1, SIGCONT);
    sleep(3);
    printf("Parent: killing both children\n");
    kill(child1, SIGKILL);
    kill(child2, SIGKILL);
}

int main() {
    child1 = fork();
    if (child1 == 0) {
        while (1) {
            printf("Process %d is alive\n", getpid());
            sleep(1);
        }
    }
    child2 = fork();
    if (child2 == 0) {
        while (1) {
            printf("Process %d is alive\n", getpid());
            sleep(1);
        }
    }

/* parent */
    struct sigaction act;
    act.sa_handler = parent_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGUSR2, &act, NULL);

    printf("Parent PID: %d. Send SIGUSR2 to start.\n", getpid());
    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);
    printf("Parent: all children terminated. Exiting.\n");
    return 40;
}
