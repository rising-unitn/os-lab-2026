#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int total = 0;

static void walk(const char *dirpath) {
  DIR *dir;
  struct dirent *entry;
  char path[PATH_MAX];

  pid_t pid = fork();
  if (pid == 0) {
    execlp("ls", "ls", dirpath, (char *)NULL);
    _exit(127);
  } else if (pid > 0) {
    waitpid(pid, NULL, 0);
  }

dir = opendir(dirpath);
if (!dir) {
  return;
}

while ((entry = readdir(dir)) != NULL) {
  if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
    continue;
  }

  snprintf(path, sizeof(path), "%s/%s", dirpath, entry->d_name);
  printf("%s\n", path);
  total++;

if (entry->d_type == DT_DIR) {
      walk(path);
    }
  }

  closedir(dir);
}

int main(int argc, char *argv[]) {
  const char *root = (argc > 1) ? argv[1] : ".";
  walk(root);
  printf("total=%d\n", total);
  return 0;
}
