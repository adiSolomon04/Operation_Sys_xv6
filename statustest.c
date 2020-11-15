#include "types.h"
#include "stat.h"
#include "user.h"

#include "fcntl.h"

//passing command line arguments
// testing the status return of child process.

int main(int argc, char *argv[])
{
    int pid = fork();
    if(pid == 0){
        printf(1, "I'm the child!\n");
        exit(57);
    } else if(pid < 0){
        printf (1, "This is fork failed\n");
        exit(0);
    }
    int status;
    wait(&status);
    printf(1, "I'm the parent, and got child status: %d\n", status);
    exit(0);
}
