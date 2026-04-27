#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    if (pipe(fd) == -1) { perror("pipe"); return 1; }
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }

if (pid == 0) {           /* child: writer */
    close(fd[0]);         /* close unused read end */
    const char *msg = "Hello from child!\n";
    write(fd[1], msg, strlen(msg));
    close(fd[1]);         /* signal EOF */
    exit(0);
}
/* parent: reader */
close(fd[1]);             /* close unused write end */
char buf[256];
ssize_t n;
while ((n = read(fd[0], buf, sizeof(buf))) > 0)
    write(STDOUT_FILENO, buf, n);

close(fd[0]);
    wait(NULL);
    return 0;
}
