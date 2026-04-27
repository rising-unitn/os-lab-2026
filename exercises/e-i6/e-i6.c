#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

typedef struct { int fd; int idx; } targ_t;

void *writer(void *arg) {
    targ_t *t = (targ_t *)arg;
    char buf[64];

int n = snprintf(buf, 64,
        "Thread %d on FD %d\n", t->idx, t->fd);
    write(t->fd, buf, n);
    return NULL;
}
#define N 4
int main(void) {
    int fd = open("threads.txt",
                O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) { perror("open"); return 1; }
    pthread_t tids[N];
    targ_t args[N];

for (int i = 0; i < N; i++) {
    args[i] = (targ_t){fd, i};
    pthread_create(&tids[i], NULL,
                   writer, &args[i]);
}
for (int i = 0; i < N; i++)
    pthread_join(tids[i], NULL);
close(fd);

fd = open("threads.txt", O_RDONLY);
    if (fd == -1) { perror("open read"); return 1; }
    char out[512];
    ssize_t r = read(fd, out, sizeof(out));
    if (r > 0) write(STDOUT_FILENO, out, r);
    close(fd);
    return 0;
}
