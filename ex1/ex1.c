// Write a program that calls `fork()`. Before calling `fork()`, have the main process access a variable
// (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process?
//    It does not change in the parent process.
// What happens to the variable when both the child and parent change the value of x?
//    In the main(), only the parent changes are saved to the variable.
//    Note: If we don't use wait() or waitpid(), the parent process will execute before the child process.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int x = 100;
  int rc = fork();

  if (rc < 0) // fork failed; exit
  {
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if (rc == 0) // child process satisfies this branch
  {
    printf("hello, child here (pid: %d) \n", (int)getpid());
    printf("x is equal to %d\n", x);
    printf("adding 20 to x makes x equal to ");
    x += 20;
    printf("%d\n\n", x);
    exit(0);
  }
  // waitpid(rc, NULL, 0);
  // or...
  wait(NULL);

  printf("hello, parent here (pid: %d) of child %d\n", (int)getpid(), rc);
  printf("x is equal to %d\n", x);
  printf("adding 40 to x makes x equal to ");
  x += 40;
  printf("%d\n\n", x);

  return 0;
}

// ****************************************** fork template ******************************************
/*
int rc = fork();

if (rc < 0) // fork failed; exit
{
  fprintf(stderr, "fork failed\n");
  exit(1);
}
else if (rc == 0) // child process satisfies this branch
{
  exit(0);
}
waitpid(rc, NULL, 0);
or...
wait(NULL);
*/
