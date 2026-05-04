#include <stdio.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
int main(void) {
    int fd = shm_open("/lab_counter",
                      O_CREAT | O_RDWR, 0644);
    ftruncate(fd, sizeof(int));
    int *counter = mmap(NULL, sizeof(int),
        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

*counter = 0;
    pid_t pid = fork();
    if (pid == 0) {
        for (int i = 0; i < 100000; i++)
            (*counter)++;
        exit(0);
    }
    for (int i = 0; i < 100000; i++)
        (*counter)++;
    wait(NULL);
    printf("Expected: 200000, Got: %d\n", *counter);
    munmap(counter, sizeof(int));
    shm_unlink("/lab_counter");
    return 0;
}
