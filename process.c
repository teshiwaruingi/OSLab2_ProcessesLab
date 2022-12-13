#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int genRandonNumber(int lower, int upper) {
 return ((random() % (upper - lower)) + lower);
}

void ChildProcess() {
  int i;
  int max_count = genRandonNumber(0, 30);
  for (i = 1; i <= max_count; i++) {
     printf("Child %d is going to sleep!\n", getpid());
     sleep(genRandonNumber(0,10));
     printf("Child %d is awake!\n Where is my parent: %d? \n",getpid(),getppid());
}
  exit(0);
};

int main(int argc, char * argv[]) {
  srandom(time(0));
  pid_t  pid;
   int    i; 
   pid = fork();
   if (pid == 0) {
        ChildProcess();
   }
   else if (pid == -1) {
     exit(1);
   }
   else {
     pid = fork();
     if (pid == 0) {
       ChildProcess();
       } 
     else if (pid == -1) {
       exit(1);
     }
     else {
       for (i=0; i<2; i++){
       pid = wait(NULL);
       printf("Child %d has completed\n", pid);}
     }
   }
}