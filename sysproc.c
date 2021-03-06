#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  int status;
    //get the kill status of the process
  if(argint(0, &status) < 0)
    return -1;
  exit(status);
  return 0;  // not reached
}

int
sys_wait(void)
{
  int* status;
  //get status int* variable.
  if(argptr(0,(char**) &status, sizeof(int*)) < 0)
    return -1;
  return wait(status);
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

int
sys_getpinfo(void)
{
  //if(pidnum<3)
  //	return getpinfo(pidnum)->pid;
  return getpinfo();
}

int 
sys_setpriority(void)
{
  int priority;
  if(argint(0, &priority) < 0)
    return -1;
    
  struct proc *curproc= myproc();
  int oldp = curproc->priority;
  if(priority>=0 && priority<=200){
  	curproc->priority = priority;
  	if(priority<oldp) //higer priority - call reschedule
  		yield();
  	return oldp;
  }
 return -1;
}
