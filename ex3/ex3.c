// Write another program using `fork()`. The child process should print "hello";
// the parent process should print "goodbye". You should ensure that the child
// process always prints first.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
  // Your code here
  // create child process
  int rc = fork();

  // fork failed; exit
  if (rc < 0)
  {
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  // child process
  else if (rc == 0)
  {
    printf("hello\n");
    exit(0);
  }

  // parent process
  wait(NULL);
  printf("goodbye\n");
  return 0;
}
