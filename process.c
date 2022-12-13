#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// generates a random number between the given lower and upper bounds
int genRandonNumber(int lower, int upper) {
  return ((random() % (upper - lower)) + lower);
}

// the code that the child process should execute
void ChildProcess() {
  int i;
  int max_count = genRandonNumber(0, 30);

  // the child process goes to sleep and wakes up a random number of times
  for (i = 1; i <= max_count; i++) {
    printf("Child %d is going to sleep!\n", getpid());
    sleep(genRandonNumber(0, 10));
    printf("Child %d is awake!\n Where is my parent: %d? \n", getpid(), getppid());
  }

  // exit the child process
  exit(0);
}

int main(int argc, char * argv[]) {
  srandom(time(0)); // seed the random number generator

  pid_t pid;
  int i;

  // create the first child process
  pid = fork();
  if (pid == 0) {
    ChildProcess();
  } else if (pid == -1) {
    exit(1);
  } else {
    // create the second child process
    pid = fork();
    if (pid == 0) {
      ChildProcess();
    } else if (pid == -1) {
      exit(1);
    } else {
      // wait for both child processes to finish
      for (i = 0; i < 2; i++) {
        pid = wait(NULL);
        printf("Child %d has completed\n", pid);
      }
    }
