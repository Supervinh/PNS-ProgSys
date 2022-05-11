#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

pid_t getpid(void);
pid_t getppid(void);

int main(int argc, char* argv[]){
    printf("Deuxième programme\n");
    printf("pid : %d et arg %s \n", getpid(), argv[0]);
    return 0;
}