#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {
    int srv = socket(AF_INET, SOCK_STREAM, 0);
    if (srv == -1) { perror("socket"); return 1; }
    int opt = 1;
    setsockopt(srv, SOL_SOCKET, SO_REUSEADDR,
               &opt, sizeof(opt));

struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_port = htons(8080),
    .sin_addr.s_addr = INADDR_ANY
};
if (bind(srv, (struct sockaddr *)&addr,
         sizeof(addr)) == -1) {
    perror("bind"); close(srv); return 1; }
if (listen(srv, 1) == -1) {
    perror("listen"); close(srv); return 1; }
printf("Listening on port 8080...\n");

int cli = accept(srv, NULL, NULL);
    if (cli == -1) { perror("accept"); close(srv); return 1; }
    char buf[256];
    ssize_t n;
    while ((n = read(cli, buf, sizeof(buf))) > 0) {
        write(cli, buf, n);            /* echo back */
        write(STDOUT_FILENO, buf, n);  /* also print */
    }
    close(cli);
    close(srv);
    return 0;
}
