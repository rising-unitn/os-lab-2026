#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void) {
    mkfifo("/tmp/ex_fifo", 0644);
    int fd = open("/tmp/ex_fifo", O_WRONLY);
    if (fd == -1) { perror("open"); return 1; }
    char line[256];
    while (fgets(line, sizeof(line), stdin)) {
        write(fd, line, strlen(line));
        if (strncmp(line, "quit", 4) == 0) break;
    }

close(fd);
    return 0;
}
