#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "vm.h"
#include "shm.h"


extern struct shmentry shmtab[MAX_SHM];


extern struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

int sys_getpinfo(void) {
  struct pinfo *ptable_user;
  if (argptr(0, (char**)&ptable_user, sizeof(*ptable_user)) < 0)
    return -1;

  struct proc *p;
  int i = 0;

  acquire(&ptable.lock);
  for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
    if (p->state != UNUSED) {
      ptable_user->pid[i] = p->pid;
      ptable_user->mem[i] = p->sz;
      safestrcpy(ptable_user->name[i], p->name, sizeof(p->name));
      i++;
    }
  }
  release(&ptable.lock);

  return 0;
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

void* sys_shmget(void) {
  struct proc *p = myproc();
  int key;
  if(argint(0, &key) < 0)
    return (void*)-1;

  for(int i = 0; i < MAX_SHM; i++){
    if(shmtab[i].key == key){
      shmtab[i].refcnt++;
      mappages(p->pgdir, (char*)(USERTOP - (i+1)*PGSIZE), PGSIZE,
               V2P(shmtab[i].frame), PTE_W|PTE_U);
      return (void*)(USERTOP - (i+1)*PGSIZE);
    }
  }

  for(int i = 0; i < MAX_SHM; i++){
    if(shmtab[i].key == 0){
      shmtab[i].key = key;
      shmtab[i].frame = kalloc();
      shmtab[i].refcnt = 1;
      memset(shmtab[i].frame, 0, PGSIZE);
      mappages(p->pgdir, (char*)(USERTOP - (i+1)*PGSIZE), PGSIZE,
               V2P(shmtab[i].frame), PTE_W|PTE_U);
      return (void*)(USERTOP - (i+1)*PGSIZE);
    }
  }

  return (void*)-1;
}

int sys_shmrelease(void) {
  int key;
  if(argint(0, &key) < 0)
    return -1;

  for(int i = 0; i < MAX_SHM; i++){
    if(shmtab[i].key == key){
      shmtab[i].refcnt--;
      if(shmtab[i].refcnt == 0){
        kfree(shmtab[i].frame);
        shmtab[i].key = 0;
      }
      return 0;
    }
  }
  return -1;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
int readcount = 0; // untuk menghitung read()
int sys_getreadcount(void) {
  return readcount;
}
int sys_set_priority(void) {
  int prio;
  if (argint(0, &prio) < 0 || prio < 0 || prio > 100)
    return -1;

  myproc()->priority = prio;
  return 0;
}