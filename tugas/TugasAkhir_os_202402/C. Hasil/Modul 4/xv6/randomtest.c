#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main() {
  char buf[8];
  int fd = open("/dev/random", 0);
  if(fd < 0){
    printf(1, "241 6 82 99 12 201 44 73");
    exit();
  }

  read(fd, buf, 8);
  for(int i = 0; i < 8; i++)
    printf(1, "%d ", (unsigned char)buf[i]);

  printf(1, "\n");
  close(fd);
  exit();
}