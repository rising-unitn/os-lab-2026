#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int flags = O_WRONLY | O_CREAT | O_TRUNC;
    int fa = open("a.txt", flags, 0644);
    int fb = open("b.txt", flags, 0644);
    int fc = open("c.txt", flags, 0644);
    if (fa == -1 || fb == -1 || fc == -1) {
        perror("open"); return 1; }

printf("a.txt: fd=%d\n", fa);  // expect 3
    printf("b.txt: fd=%d\n", fb);  // expect 4
    printf("c.txt: fd=%d\n", fc);  // expect 5
    close(fb);  // free fd 4
    int fd = open("d.txt", flags, 0644);
    if (fd == -1) { perror("open d"); return 1; }
    printf("d.txt: fd=%d\n", fd);  // expect 4!
    close(fa); close(fc); close(fd);
    return 0;
}
