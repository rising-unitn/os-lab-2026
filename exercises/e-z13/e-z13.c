#include <pthread.h>
#include <stdio.h>

#define NBUF   8      /* circular buffer capacity (slots) */
#define NITEMS 100    /* total items to produce/consume   */

/* Shared buffer — all fields protected by mutex m */
static int buf[NBUF], head = 0, tail = 0, count = 0;
static pthread_mutex_t m         = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  not_full  = PTHREAD_COND_INITIALIZER;
static pthread_cond_t  not_empty = PTHREAD_COND_INITIALIZER;

static void *producer(void *arg) {
  (void)arg;
  for (int i = 1; i <= NITEMS; i++) {
    pthread_mutex_lock(&m);
    /* while — not if — guards against spurious wake-ups */
    while (count == NBUF)
      pthread_cond_wait(&not_full, &m);
    buf[head] = i;
    head = (head + 1) % NBUF;
    count++;
    pthread_cond_signal(&not_empty); /* wake a waiting consumer */
    pthread_mutex_unlock(&m);
  }
  return NULL;
}

static void *consumer(void *arg) {
  (void)arg;
  for (int seen = 0; seen < NITEMS; seen++) {
    pthread_mutex_lock(&m);
    while (count == 0)
      pthread_cond_wait(&not_empty, &m);
    int v = buf[tail];
    tail = (tail + 1) % NBUF;
    count--;
    pthread_cond_signal(&not_full); /* wake a waiting producer */
    pthread_mutex_unlock(&m);
    printf("consumed %d\n", v);
  }
  return NULL;
}

int main(void) {
  pthread_t p, c;
  pthread_create(&p, NULL, producer, NULL);
  pthread_create(&c, NULL, consumer, NULL);
  pthread_join(p, NULL);
  pthread_join(c, NULL);
  puts("done");
  return 0;
}
