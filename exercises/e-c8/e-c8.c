#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd = open("output.txt",
                  O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) { perror("open"); return 1; }
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }

if (pid == 0) {
    dup2(fd, STDOUT_FILENO);
    close(fd);
    printf("Hello from redirected stdout!\n");
    fflush(stdout);
    exit(0);
}
close(fd);
printf("Hello from parent!\n");
wait(NULL);

/* read and display file contents */
    fd = open("output.txt", O_RDONLY);
    char buf[256];
    ssize_t n = read(fd, buf, sizeof(buf));
    printf("File contains: ");
    write(STDOUT_FILENO, buf, n);
    close(fd);
    return 0;
}
