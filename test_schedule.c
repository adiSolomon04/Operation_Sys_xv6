//
// Created by eranaf on 14/12/2020.
//

#include "types.h"
#include "stat.h"
#include "user.h"

#include "fcntl.h"

//passing command line arguments

int main(int argc, char **argv)
{
	 int newprior = atoi(argv[1]);
     int myPid = getpid();
     int oldPrior = setpriority(newprior);
     printf(1, "I'm the father - pid %d! change my priority to %d from %d\n",myPid,newprior,oldPrior);
	
    int pid = fork();
	for(int j=0; j<1000000; j++){}

	
    if(pid == 0){
        int newprior = atoi(argv[2]);
        int myPid = getpid();
        int oldPrior = setpriority(newprior);
        printf(1, "I'm the child - pid %d! change my priority to %d from %d\n",myPid,newprior,oldPrior);
        for(int i=0;i<10;i++){
			for(int j=0; j<1000000; j++){}
			printf(1, "%d - <pid = %d, prior= %d>\n ", i, myPid,newprior);
		}
        exit(0);
    } else if(pid < 0){
        printf (1, "This is fork failed\n");
        exit(0);
    }else{
        for(int i=0;i<10;i++){
			for(int j=0; j<1000000; j++){}
			printf(1, "%d - <pid = %d, prior= %d>\n ", i, myPid,newprior);
		}
    }
    wait(0);
    exit(0);
}
