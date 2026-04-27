#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) { perror("socket"); return 1; }
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = htonl(INADDR_LOOPBACK)
    };

if (connect(sock, (struct sockaddr *)&addr,
                sizeof(addr)) == -1) {
        perror("connect"); close(sock); return 1; }
    const char *msg = "Hello, server!\n";
    write(sock, msg, strlen(msg));
    char buf[256];
    ssize_t n = read(sock, buf, sizeof(buf));
    if (n > 0) write(STDOUT_FILENO, buf, n);
    close(sock);
    return 0;
}
