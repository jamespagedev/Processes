// Write a program that opens the text.txt file (with the `fopen()` library call) located in this directory
// and then calls `fork()` to create a new process.
// Can both the child and parent access the file descriptor returned by `fopen()`?
//    Yes, the order in which they do depends on if wait() was called or not.
// What happens when they are written to the file concurrently?
//    Answer I think is best described here -> https://stackoverflow.com/questions/12300676/multiple-processes-write-to-the-same-file-c
//    (even though I can't reproduce this)...
/*    I think it could be possible that the thread control changes in exactly that moment
      so that the second thread writes before the file position was updated.
      So it overwrites the data the other process just wrote."
*/
//    I also agree with having two or more processes write to the same file is a recipee for disaster.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
  // Your code here
  // open file with read/write privileges
  FILE *f;
  f = fopen("text.txt", "r+");
  if (f == NULL)
  {
    printf("File not created");
    return 1;
  }

  // strings for child and parent processes to write in file
  char *p_str = "I am the parent\n";
  char *c_str = "I am the child\n";

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
    fprintf(f, "%s\n", c_str);
    exit(0);
  }

  // parent process
  wait(NULL);
  fprintf(f, "%s\n", p_str);
  fclose(f);
  return 0;
}

// ******************************************* fopen MODES *******************************************
// source -> https://www.programiz.com/c-programming/c-file-input-output
/*
* -> Most popular ones I like to use
*   r   |	Open for reading.
If the file does not exist, fopen() returns NULL.

    rb  | Open for reading in binary mode.
If the file does not exist, fopen() returns NULL.

*   w   | Open for writing.
If the file exists, its contents are overwritten. If the file does not exist, it will be created.

    wb  | Open for writing in binary mode.
If the file exists, its contents are overwritten. If the file does not exist, it will be created.

    a   | Open for append. i.e, Data is added to end of file.
If the file does not exists, it will be created.

    ab  | Open for append in binary mode. i.e, Data is added to end of file.
If the file does not exists, it will be created.

*   r+  | Open for both reading and writing.
If the file does not exist, fopen() returns NULL.

    rb+ | Open for both reading and writing.
If the file does not exist, fopen() returns NULL.

*   w+  | Open for both reading and writing.
If the file exists, its contents are overwritten. If the file does not exist, it will be created.

    wb+ | Open for both reading and writing in binary mode.
If the file exists, its contents are overwritten. If the file does not exist, it will be created.

*   a+  | Open for both reading and appending.
If the file does not exists, it will be created.

    ab+ | Open for both reading and appending in binary mode.
If the file does not exists, it will be created.
*/