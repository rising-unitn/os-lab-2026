#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {
    int fd[2];
    if (pipe(fd) == -1) { perror("pipe"); return 1; }
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }

if (pid == 0) {
        close(fd[0]);
        const char *msg = "The answer is 42\n";
        write(fd[1], msg, strlen(msg));
        close(fd[1]);
        exit(0);
    }
    close(fd[1]);
    char buf[128];
    ssize_t n = read(fd[0], buf, sizeof(buf));
    if (n > 0) write(STDOUT_FILENO, buf, n);
    close(fd[0]);
    wait(NULL);
    return 0;
}
