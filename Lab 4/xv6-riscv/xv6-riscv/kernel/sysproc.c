#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
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

uint64
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
  backtrace();
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

void sys_pcbread(void)
{
  struct proc *p = myproc();
  printf("lock %p\n", &(p->lock));
  printf("state=%d\n", (p->state));
  printf("parent %p\n", p->parent);
  printf("chan %p\n", p->chan);
  printf("killed %d\n", p->killed);
  printf("xstate %d\n", p->xstate);
  printf("pid %d\n", p->pid);
  printf("kstack %p\n", p->kstack);
  printf("sz %p\n", p->sz);
  printf("pagetable %p\n", p->pagetable);
  printf("trapframe %p\n", p->tf);
  printf("context %p\n", &(p->context));
  printf("file %p\n", p->ofile);
  printf("inode %p\n", p->cwd);
  printf("name %s\n", p->name);
}