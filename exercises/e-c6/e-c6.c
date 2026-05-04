#include <stdio.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

int main(void) {
    int fd = shm_open("/lab_counter2",
                      O_CREAT | O_RDWR, 0644);
    ftruncate(fd, sizeof(int));
    int *counter = mmap(NULL, sizeof(int),
        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

close(fd);
*counter = 0;
sem_t *sem = sem_open("/lab_sem",
                      O_CREAT, 0644, 1);
pid_t pid = fork();
if (pid == 0) {
    for (int i = 0; i < 100000; i++) {
        sem_wait(sem);
        (*counter)++;
        sem_post(sem);
    }
    exit(0);
}

for (int i = 0; i < 100000; i++) {
        sem_wait(sem);
        (*counter)++;
        sem_post(sem);
    }
    wait(NULL);
    printf("Expected: 200000, Got: %d\n", *counter);
    sem_close(sem);
    sem_unlink("/lab_sem");
    munmap(counter, sizeof(int));
    shm_unlink("/lab_counter2");
    return 0;
}
