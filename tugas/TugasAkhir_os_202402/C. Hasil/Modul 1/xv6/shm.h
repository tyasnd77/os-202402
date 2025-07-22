#ifndef SHM_H
#define SHM_H

#define MAX_SHM 64

struct shmentry {
  int key;
  int refcnt;
  char *frame;
};

extern struct shmentry shmtab[MAX_SHM];

#endif