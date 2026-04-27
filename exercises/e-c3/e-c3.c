#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pattern>\n", argv[0]);
        return 1;
    }
    int pipe1[2], pipe2[2];
    pipe(pipe1); pipe(pipe2);

pid_t p1 = fork();
if (p1 == 0) {
    close(pipe1[0]); close(pipe2[0]); close(pipe2[1]);
    dup2(pipe1[1], STDOUT_FILENO);
    close(pipe1[1]);
    execlp("ls", "ls", NULL);
    perror("execlp ls"); exit(1);
}

pid_t p2 = fork();
if (p2 == 0) {
    close(pipe1[1]); close(pipe2[0]);
    dup2(pipe1[0], STDIN_FILENO);
    dup2(pipe2[1], STDOUT_FILENO);
    close(pipe1[0]); close(pipe2[1]);
    execlp("grep", "grep", argv[1], NULL);
    perror("execlp grep"); exit(1);
}

pid_t p3 = fork();
    if (p3 == 0) {
        close(pipe1[0]); close(pipe1[1]); close(pipe2[1]);
        dup2(pipe2[0], STDIN_FILENO);
        close(pipe2[0]);
        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc"); exit(1);
    }
    close(pipe1[0]); close(pipe1[1]);
    close(pipe2[0]); close(pipe2[1]);
    wait(NULL); wait(NULL); wait(NULL);
    return 0;
}
