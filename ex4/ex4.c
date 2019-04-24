// Write a program that calls `fork()` and then calls some form of `exec()`
// to run the program `/bin/ls`. Try a few variants of `exec()`, such as
// `execl()`, `execle()`, `execv()`, and others.
// Why do you think there are so many variants of the same basic call?

#include <stdio.h>
#include <unistd.h> // used for exec calls and pid_t
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h> // used for pid_t

void forker(int nprocesses)
{
  pid_t pid;

  if (nprocesses > 0)
  {
    if ((pid = fork()) < 0)
    {
      perror("fork");
    }
    //Child stuff here
    else if (pid == 0)
    {
      // Child Process execl
      if (nprocesses == 6)
      {
        /*  The following example executes the ls command,
        specifying the pathname of the executable ( /bin/ls)
        and using arguments supplied directly to the command
        to produce single-column output.
        */
        wait(NULL);
        printf("\nChild Process execl:\n");
        execl("/bin/ls", "ls", "-1", (char *)0); // returns child process, no need for `exit()`
      }
      // Child Process execle
      else if (nprocesses == 5)
      {
        /*  The following example is similar to Using execl().
        In addition, it specifies the environment
        for the new process image using the env argument.
        */
        printf("\nChild Process execle:\n");
        char *env_le[] = {"HOME=/usr/jamespage", "LOGNAME=home", (char *)0};
        execle("/bin/ls", "ls", "-l", (char *)0, env_le); // returns child process, no need for `exit()`
      }
      // Child Process execlp
      else if (nprocesses == 4)
      {
        /*  The following example searches for the location of the
        ls command among the directories specified
        by the PATH environment variable.
        */
        printf("\nChild Process execlp:\n");
        execlp("ls", "ls", "-l", (char *)0); // returns child process, no need for `exit()`
      }
      // Child Process execv
      else if (nprocesses == 3)
      {
        /*  The following example passes arguments
        to the ls command in the cmd array.
        */
        printf("\nChild Process execv:\n");
        char *cmd_cv[] = {"ls", "-l", (char *)0};
        execv("/bin/ls", cmd_cv); // returns child process, no need for `exit()`
      }
      // Child Process execve
      else if (nprocesses == 2)
      {
        /*  The following example passes arguments to the ls command
        in the cmd array, and specifies the environment for the
        new process image using the env argument.
        */
        printf("\nChild Process execve:\n");
        char *cmd_ve[] = {"ls", "-l", (char *)0};
        char *env_ve[] = {"HOME=/usr/jamespage", "LOGNAME=home", (char *)0};
        execve("/bin/ls", cmd_ve, env_ve);
      }
      // Child Process execvp
      else if (nprocesses == 1)
      {
        /*  The following example searches for the location of the
        ls command among the directories specified by the
        PATH environment variable, and passes arguments to the
        ls command in the cmd array.
        */
        printf("\nChild Process execvp:\n");
        char *cmd_vp[] = {"ls", "-l", (char *)0};
        execvp("ls", cmd_vp);
      }
      // Default unhandled child process
      else
      {
        //Child stuff here
        printf("\nChild %d end\n", nprocesses);
        exit(0);
      }
    }
    // Parent
    else if (pid > 0)
    {
      wait(NULL);
      forker(nprocesses - 1);
    }
  }
}

int main(void)
{
  // Your code here
  // create and execute 6 child process(es)
  /*
    execl
    execle
    execlp
    execv
    execve
    execvp
  */

  forker(6);

  // parent process
  wait(NULL);
  printf("\nmain() Parent Process\n");
  return 0;
}

// ******************************************** source(s) ********************************************
/*
  http://pubs.opengroup.org/onlinepubs/009695399/functions/environ.html
*/