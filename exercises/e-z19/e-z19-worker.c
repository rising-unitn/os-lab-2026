#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void) {
  /* XOR with PID so each worker has a different random sequence */
  srand((unsigned)time(NULL) ^ (unsigned)getpid());
  while (1) {
    printf("worker PID=%d alive\n", getpid());
    fflush(stdout);
    sleep(1);
    /* ~5% crash probability each second */
    if ((rand() % 20) == 0) {
      fprintf(stderr, "worker PID=%d crashing!\n", getpid());
      return 1;
    }
  }
}
