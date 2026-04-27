#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(void) {
    mkfifo("/tmp/lab_fifo", 0644);
    int fd = open("/tmp/lab_fifo", O_WRONLY);
    if (fd == -1) { perror("open"); return 1; }
    const char *msg = "Message via FIFO\n";
    write(fd, msg, strlen(msg));
    close(fd);
    return 0;
}
