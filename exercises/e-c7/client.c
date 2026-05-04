#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <msg>\n", argv[0]);
        return 1;
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);

struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(9000),
        .sin_addr.s_addr = htonl(INADDR_LOOPBACK)
    };
    connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    write(sock, argv[1], strlen(argv[1]));
    char buf[256];
    ssize_t n = read(sock, buf, sizeof(buf));
    buf[n] = '\0';
    printf("Server replied: %s\n", buf);
    close(sock);
    return 0;
}
