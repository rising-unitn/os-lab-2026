#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

static volatile time_t first_sigint_time = 0;
static volatile int flag = 0;

void handler(int signum) {
    (void)signum;
    if (flag && (time(NULL) - first_sigint_time) < 3) {
        printf("\nSecond SIGINT within 3 seconds. Exiting.\n");
        exit(0);
    }
    printf("\nCaught SIGINT! Press Ctrl+C again within 3 seconds to quit.\n");
    first_sigint_time = time(NULL);
    flag = 1;
}

int main() {
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);

    while (1) {
        printf("Running...\n");
        sleep(1);
        if (flag && (time(NULL) - first_sigint_time) >= 3) {
            flag = 0;
        }
    }
    return 0;
}
