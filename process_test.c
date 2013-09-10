#include <stdio.h>

int main(int argc, char **argv)
{
  int pid;
  pid = fork();
  if (pid < 0) {
    fprintf(stderr, "Fork Failed!\n");
    exit(-1);
  }
  else if (pid == 0)
  {
    printf("Child process %d start\n", pid);
    execlp("/bin/ls", "ls", NULL);
  }
  else
  {
    pid = wait(NULL);
    printf("Child process %d complete.\n", pid);
    exit(0);
  }

  return 0;
}
