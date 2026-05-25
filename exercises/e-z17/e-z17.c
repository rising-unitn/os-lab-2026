#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  /* Open replacement files before redirecting */
  int out_fd = open("z17.out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  int err_fd = open("z17.err", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (out_fd < 0 || err_fd < 0) { perror("open"); return 1; }

  /* dup2(src, dst): closes dst then duplicates src onto dst */
  dup2(out_fd, STDOUT_FILENO);  /* stdout -> z17.out */
  dup2(err_fd, STDERR_FILENO);  /* stderr -> z17.err */
  close(out_fd);                /* original fds no longer needed */
  close(err_fd);

  printf("This goes to z17.out\n");
  fprintf(stderr, "This goes to z17.err\n");
  fflush(NULL);   /* flush all stdio buffers before fork */

/* Fork: child inherits the redirected stdout/stderr */
pid_t pid = fork();
if (pid == 0) {
  printf("child also writes to z17.out\n");
  fprintf(stderr, "child also writes to z17.err\n");
  _exit(0);
}
wait(NULL);

/* Restore stdout to the terminal for a final diagnostic message */
  int tty = open("/dev/tty", O_WRONLY);
  if (tty >= 0) {
    dup2(tty, STDOUT_FILENO);
    dup2(tty, STDERR_FILENO);
    close(tty);
  }
  printf("Done — check z17.out and z17.err\n");
  return 0;
}
