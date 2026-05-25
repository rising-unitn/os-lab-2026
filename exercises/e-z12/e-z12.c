#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/* Flags set inside signal handlers — volatile sig_atomic_t is signal-safe */
static volatile sig_atomic_t got_usr1 = 0;
static volatile sig_atomic_t got_usr2 = 0;

static void on_usr1(int s) { (void)s; got_usr1 = 1; }
static void on_usr2(int s) { (void)s; got_usr2 = 1; }

/* Block or unblock a single signal via sigprocmask */
static void block_sig(int sig, int how) {
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, sig);
  sigprocmask(how, &set, NULL);
}

int main(void) {
  /* Block BOTH signals BEFORE fork — prevents signal arriving
   * before sigsuspend() is entered in either process */
  block_sig(SIGUSR1, SIG_BLOCK);
  block_sig(SIGUSR2, SIG_BLOCK);

  struct sigaction sa = {0};
  sa.sa_handler = on_usr1; sigaction(SIGUSR1, &sa, NULL);
  sa.sa_handler = on_usr2; sigaction(SIGUSR2, &sa, NULL);

  sigset_t empty; sigemptyset(&empty); /* mask with nothing blocked */

  pid_t child = fork();
  if (child < 0) { perror("fork"); return 1; }

if (child == 0) {
    /* ---- CHILD ---- */
    kill(getppid(), SIGUSR2);              /* tell parent: ready   */
    while (!got_usr1) sigsuspend(&empty); /* sleep until SIGUSR1  */
    printf("child: got ack from parent\n");
    _exit(0);
  }

  /* ---- PARENT ---- */
  while (!got_usr2) sigsuspend(&empty);  /* sleep until SIGUSR2  */
  printf("parent: child is ready, sending ack\n");
  kill(child, SIGUSR1);

  wait(NULL);
  printf("parent: done\n");
  return 0;
}
