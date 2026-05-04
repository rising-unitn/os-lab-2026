#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {
    int srv = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(srv, SOL_SOCKET, SO_REUSEADDR,
               &opt, sizeof(opt));

struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_port = htons(9000),
    .sin_addr.s_addr = INADDR_ANY
};
bind(srv, (struct sockaddr *)&addr, sizeof(addr));
listen(srv, 1);
printf("Listening on port 9000...\n");
int cli = accept(srv, NULL, NULL);
char buf[256];
ssize_t n = read(cli, buf, sizeof(buf));

for (ssize_t i = 0; i < n; i++)
        buf[i] = toupper((unsigned char)buf[i]);
    write(cli, buf, n);
    close(cli);
    close(srv);
    return 0;
}
