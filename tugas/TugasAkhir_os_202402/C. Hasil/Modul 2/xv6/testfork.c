#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int pid = fork();
  if(pid < 0){
    printf(1, "Fork failed\n");
  } else if(pid == 0){
    printf(1, "Child reads: A\n");
  } else {
    printf(1, "Parent reads: B\n");
    wait();
  }
  exit();
}