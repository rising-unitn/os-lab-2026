#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(void) {
    int fd = open("shared.txt",
                  O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) { perror("open"); return 1; }
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }

char buf[64];
if (pid == 0) {
    int n = snprintf(buf, sizeof(buf),
              "Child  PID=%d\n", getpid());
    write(fd, buf, n);
    close(fd);
    exit(0);
}
int n = snprintf(buf, sizeof(buf),
          "Parent PID=%d\n", getpid());
write(fd, buf, n);
wait(NULL);

close(fd);
    fd = open("shared.txt", O_RDONLY);
    if (fd == -1) { perror("open read"); return 1; }
    char out[256];
    ssize_t r = read(fd, out, sizeof(out));
    if (r > 0) write(STDOUT_FILENO, out, r);
    close(fd);
    return 0;
}
