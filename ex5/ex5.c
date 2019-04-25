// Write a program that forks a child and creates a shared pipe
// between the parent and child processes. Have the child write
// the three messages to the parent and have the parent print out
// the messages.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MSGSIZE 16

char *msg1 = "hello world #1";
char *msg2 = "hello world #2";
char *msg3 = "hello world #3";

int main(void)
{
  // Your code here
  // create pipe and buffer
  char buf[500];
  int fd[2];
  int io_one[2];
  int io_two[2];
  int io_three[2];

  // fd[0] read end
  // fd[1] write end
  pipe(fd);
  pipe(io_one);
  pipe(io_two);
  pipe(io_three);

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
    // Intro Messege
    char intro_messege[3][9] = {"I'm", "a", "CHILD!!!"};
    write(fd[1], intro_messege[0], strlen(intro_messege[0]) + 1); // add 1 to account for `\0` char
    write(fd[1], intro_messege[1], strlen(intro_messege[1]) + 1); // add 1 to account for `\0` char
    write(fd[1], intro_messege[2], strlen(intro_messege[2]) + 1); // add 1 to account for `\0` char

    // Three Messeges
    char messeges[3][17] = {"I want toys!", "I want a cookie!", "Lets Play!!!"};

    // First Messege
    write(io_one[1], messeges[0], strlen(messeges[0]) + 1); // add 1 to account for `\0` char

    // Second Messege
    write(io_two[1], messeges[1], strlen(messeges[1]) + 1); // add 1 to account for `\0` char

    // Third Messege
    write(io_three[1], messeges[2], strlen(messeges[2]) + 1); // add 1 to account for `\0` char
    exit(0);
  }

  // parent process
  wait(NULL);

  // Intro Messege
  int messeges_read = read(fd[0], buf, sizeof buf);
  write(STDOUT_FILENO, buf, messeges_read);
  printf("\n");

  // First Messege
  int first_msg = read(io_one[0], buf, sizeof buf);
  write(STDOUT_FILENO, buf, first_msg);
  printf("\n");

  // Second Messege
  int second_msg = read(io_two[0], buf, sizeof buf);
  write(STDOUT_FILENO, buf, second_msg);
  printf("\n");

  // Third Messege
  int third_msg = read(io_three[0], buf, sizeof buf);
  write(STDOUT_FILENO, buf, third_msg);
  printf("\n");

  return 0;
}
