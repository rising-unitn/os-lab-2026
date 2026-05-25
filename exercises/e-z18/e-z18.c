#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static pthread_mutex_t A = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t B = PTHREAD_MUTEX_INITIALIZER;

/* ---- DEADLOCK PATTERN -----
 *   T1: lock A  →  lock B
 *   T2: lock B  →  lock A   ← opposite order!
 * If both threads pass their first lock before reaching the second:
 *   T1 holds A, waits for B
 *   T2 holds B, waits for A  =>  circular wait  =>  deadlock
 *
 * FIX: enforce a global ordering — always acquire A before B.
 * No thread can hold B without first holding A, so circular wait
 * becomes impossible.
 * ------------------------------------------------------- */

/* Both threads use the SAME lock order: A first, then B */
static void *t1(void *x) {
  (void)x;
  pthread_mutex_lock(&A);  /* always first  */
  usleep(50000);           /* widen race window for demo */
  pthread_mutex_lock(&B);  /* always second */
  puts("T1 in critical section");
  pthread_mutex_unlock(&B);
  pthread_mutex_unlock(&A);
  return NULL;
}

static void *t2(void *x) {
  (void)x;
  pthread_mutex_lock(&A);  /* same order as T1 */
  usleep(50000);
  pthread_mutex_lock(&B);
  puts("T2 in critical section");
  pthread_mutex_unlock(&B);
  pthread_mutex_unlock(&A);
  return NULL;
}

int main(void) {
  pthread_t x, y;
  pthread_create(&x, NULL, t1, NULL);
  pthread_create(&y, NULL, t2, NULL);
  pthread_join(x, NULL); pthread_join(y, NULL);
  puts("no deadlock: program completed normally");
  return 0;
}
