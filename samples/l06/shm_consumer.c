#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main(void) {
    int fd = shm_open("/lab_shm", O_RDONLY, 0);
    if (fd == -1) { perror("shm_open"); return 1; }
    char *ptr = mmap(NULL, 4096,
        PROT_READ, MAP_SHARED, fd, 0);
    close(fd);
    printf("Read: %s\n", ptr);
    munmap(ptr, 4096);
    shm_unlink("/lab_shm"); /* clean up */
    return 0;
}
