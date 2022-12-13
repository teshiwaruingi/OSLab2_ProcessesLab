#include <stdio.h>
#include <sys/types.h>

// the maximum number of lines that each process should print
#define MAX_COUNT 200

// the function that the child process should execute
void ChildProcess(void);

// the function that the parent process should execute
void ParentProcess(void);

void main(void)
{
  pid_t pid;

  // create a child process
  pid = fork();

  // check if the child process was successfully created
  if (pid == 0)
  {
    // execute the code for the child process
    ChildProcess();
  }
  else
  {
    // execute the code for the parent process
    ParentProcess();
  }
}

void ChildProcess(void)
{
  int i;

  // print the lines from the child process
  for (i = 1; i <= MAX_COUNT; i++)
    printf("   This line is from child, value = %d\n", i);

  // print a message when the child process is done
  printf("   *** Child process is done ***\n");
}

void ParentProcess(void)
{
  int i;

  // print the lines from the parent process
  for (i = 1; i <= MAX_COUNT; i++)
    printf("This line is from parent, value = %d\n", i);

  // print a message when the parent process is done
  printf("*** Parent is done ***\n");
}
