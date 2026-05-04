#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd = open("/tmp/ex_fifo", O_RDONLY);
    if (fd == -1) { perror("open"); return 1; }
    char buf[256];
    ssize_t n;

while ((n = read(fd, buf, sizeof(buf) - 1)) > 0) {
        buf[n] = '\0';
        printf("%s", buf);
        if (strncmp(buf, "quit", 4) == 0) break;
    }
    close(fd);
    unlink("/tmp/ex_fifo");
    return 0;
}
