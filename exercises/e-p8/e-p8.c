#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

int main(void) {
    char line[MAX_LINE];

    while (1) {
        printf("unitn-shell$ ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break; /* EOF */

        /* strip trailing newline */
        line[strcspn(line, "\n")] = '\0';

if (strlen(line) == 0)
    continue;

/* check for background execution */
int background = 0;
size_t len = strlen(line);
if (len > 0 && line[len - 1] == '&') {
    background = 1;
    line[len - 1] = '\0';
    /* trim trailing spaces */
    while (strlen(line) > 0 && line[strlen(line) - 1] == ' ')
        line[strlen(line) - 1] = '\0';
}

/* tokenise the command */
char *args[MAX_ARGS];
int argc = 0;
char *token = strtok(line, " ");
while (token != NULL && argc < MAX_ARGS - 1) {
    args[argc++] = token;
    token = strtok(NULL, " ");
}
args[argc] = NULL;

if (argc == 0)
    continue;

pid_t pid = fork();
if (pid < 0) {
    perror("fork failed");
    continue;
}

if (pid == 0) {
    /* child: execute the command */
    execvp(args[0], args);
    perror("exec failed");
    exit(1);
}

/* parent */
        if (!background)
            waitpid(pid, NULL, 0);
        else
            printf("[bg] %d\n", pid);
    }

    printf("\n");
    return 0;
}
