#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"
char buf[512];


void cat1(int fdRead,int fdWrite1,int fdWrite2)
{
  int n;
      
//  while((
n = read(fdRead, buf, sizeof(buf));
// > 0) {
    int a = write(fdWrite1, buf, n);
    int b = write(fdWrite2, buf, n);
    if ( a != n || b != n) {	
      printf(1, "tee: write error\n");
      exit();
    }
  
  if(n < 0){
    printf(1, "tee: read error\n");
    exit();
  }
}
void cat2(int fdRead,int fdWrite)
{
  int n;
      
  while((n = read(fdRead, buf, sizeof(buf))) > 0) {
    int a = write(fdWrite, buf, n);
    if ( a != n) {	
      printf(1, "tee: write error\n");
      exit();
    }
  }
  if(n < 0){
    printf(1, "tee: read error\n");
    exit();
  }
}
int main(int arg, char *argv[])
{
	//printf(1, "arg= %d \n", arg);	
	if (arg<2){
	    printf(1, "tee: error\n");
	}
	if(arg == 2){
	   int fd = open(argv[1],O_WRONLY|O_CREATE);
	   cat1(0,1,fd);     	      

	}
	else{
	   int fdRead = open(argv[1],O_RDONLY);
	   int fdWrite = open(argv[2],O_WRONLY|O_CREATE);
	   cat2(fdRead, fdWrite);
	}
	exit();
}
