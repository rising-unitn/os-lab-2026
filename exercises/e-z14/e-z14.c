#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

/* Struct lives in shared memory so sem_init pshared=1 works correctly */
typedef struct {
  int   readers; /* number of active readers      */
  int   value;   /* shared data being protected   */
  sem_t mutex;   /* protects the 'readers' counter */
  sem_t rw;      /* exclusive access for writers  */
} shared_t;

int main(void) {
  int fd = shm_open("/z14_rw", O_CREAT | O_RDWR, 0600);
  if (fd < 0) { perror("shm_open"); return 1; }
  ftruncate(fd, sizeof(shared_t));
  shared_t *s = mmap(NULL, sizeof(shared_t),
                     PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  s->readers = 0; s->value = 0;
  sem_init(&s->mutex, /*pshared=*/1, 1);
  sem_init(&s->rw,    /*pshared=*/1, 1);

/* Writer child — needs exclusive access via rw semaphore */
if (fork() == 0) {
  sem_wait(&s->rw);
  s->value += 10;
  printf("writer: value -> %d\n", s->value);
  sem_post(&s->rw);
  _exit(0);
}

/* Two reader children — Reader-Priority entry/exit protocol */
for (int i = 0; i < 2; i++) {
  if (fork() == 0) {
    /* Entry: first reader blocks writers */
    sem_wait(&s->mutex);
    s->readers++;
    if (s->readers == 1) sem_wait(&s->rw);
    sem_post(&s->mutex);

    printf("reader %d: value = %d\n", i, s->value);

/* Exit: last reader re-enables writers */
      sem_wait(&s->mutex);
      s->readers--;
      if (s->readers == 0) sem_post(&s->rw);
      sem_post(&s->mutex);
      _exit(0);
    }
  }
  for (int i = 0; i < 3; i++) wait(NULL);
  sem_destroy(&s->mutex); sem_destroy(&s->rw);
  munmap(s, sizeof(shared_t)); shm_unlink("/z14_rw");
  return 0;
}
