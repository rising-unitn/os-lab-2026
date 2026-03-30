#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        /* child process */
        printf("I am the child, my PID is %d, my parent's PID is %d\n",
               getpid(), getppid());
        return 0;
    }

else {
        /* parent process */
        wait(NULL);
        printf("I am the parent, my PID is %d, my child's PID was %d\n",
               getpid(), pid);
        return 0;
    }
}
