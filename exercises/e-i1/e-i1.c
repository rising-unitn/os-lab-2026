#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    const char *msg = "Hello, file descriptors!\n";
    int fd = open("hello.txt",
                  O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) { perror("open write"); return 1; }
    if (write(fd, msg, strlen(msg)) == -1) {
        perror("write"); close(fd); return 1; }

close(fd);
    fd = open("hello.txt", O_RDONLY);
    if (fd == -1) { perror("open read"); return 1; }
    char buf[128];
    ssize_t n = read(fd, buf, sizeof(buf));
    if (n == -1) {
        perror("read"); close(fd); return 1;
    }
    write(STDOUT_FILENO, buf, n);
    close(fd);
    return 0;
}
