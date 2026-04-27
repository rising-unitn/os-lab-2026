#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd = open("/tmp/lab_fifo", O_RDONLY);
    if (fd == -1) { perror("open"); return 1; }
    char buf[256];
    ssize_t n = read(fd, buf, sizeof(buf));
    if (n > 0) write(STDOUT_FILENO, buf, n);
    close(fd);
    unlink("/tmp/lab_fifo");
    return 0;
}
