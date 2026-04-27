#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {
    int p2c[2], c2p[2]; /* parent-to-child, child-to-parent */
    pipe(p2c); pipe(c2p);
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }

if (pid == 0) {
    close(p2c[1]); close(c2p[0]);
    char buf[64];
    ssize_t n = read(p2c[0], buf, sizeof(buf) - 1);
    buf[n] = '\0';
    int val = atoi(buf) * 2;
    int len = sprintf(buf, "%d", val);
    write(c2p[1], buf, len);
    close(p2c[0]); close(c2p[1]);
    exit(0);
}

close(p2c[0]); close(c2p[1]);
    const char *num = "21";
    write(p2c[1], num, strlen(num));
    close(p2c[1]);
    char buf[64];
    ssize_t n = read(c2p[0], buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("Sent %s, received %s\n", num, buf);
    close(c2p[0]);
    wait(NULL);
    return 0;
}
