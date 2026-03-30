#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void spawn(int p, int depth) {
    if (depth <= 0)
        return;

    for (int i = 0; i < p; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }

if (pid == 0) {
        /* child: write PID info to {pid}.txt */
        char filename[64];
        snprintf(filename, sizeof(filename), "%d.txt", getpid());
        FILE *f = fopen(filename, "w");
        if (f) {
            fprintf(f, "PID: %d, Parent PID: %d\n", getpid(), getppid());
            fclose(f);
        }
        /* recurse into the next layer */
        spawn(p, depth - 1);
        exit(0);
    }
}

/* parent: wait for all children */
    for (int i = 0; i < p; i++)
        wait(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <p> <d>\n", argv[0]);
        return 1;
    }

int p = atoi(argv[1]);
    int d = atoi(argv[2]);

    if (p <= 0 || d <= 0 || d >= 10 || p <= d) {
        fprintf(stderr, "Invalid arguments: need p > 0, d > 0, d < 10, p > d\n");
        return 1;
    }

    spawn(p, d);
    return 0;
}
