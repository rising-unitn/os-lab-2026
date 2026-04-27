#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main(void) {
    int fd = shm_open("/lab_shm", O_CREAT | O_RDWR, 0644);
    if (fd == -1) { perror("shm_open"); return 1; }
    ftruncate(fd, 4096);
    char *ptr = mmap(NULL, 4096,
        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

close(fd);
    sprintf(ptr, "Hello from producer! PID=%d", getpid());
    printf("Written: %s\n", ptr);
    munmap(ptr, 4096);
    /* do NOT unlink: consumer needs it */
    return 0;
}
