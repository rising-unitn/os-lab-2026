#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_func(void *arg) {
    (void)arg;
    printf("Hello from the thread! My ID: %lu\n",
           (unsigned long)pthread_self());
    pthread_exit(NULL);
}

int main(void) {
    pthread_t tid;
    if (pthread_create(&tid, NULL,
                       thread_func, NULL) != 0) {
        perror("pthread_create failed");
        return 1;
    }
    pthread_join(tid, NULL);
    printf("Thread finished.\n");
    return 0;
}
