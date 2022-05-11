#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

pid_t getpid(void);
pid_t getppid(void);

int main(){
    //int pid_pere = getpid();
    switch (fork()) {
        case -1 :
            perror("fork");
            exit(1);
        case 0 :
            //while (getppid() == pid_pere) 
                sleep(1);
            printf("Fils dont le père est : %d\n", getppid());
            exit(0);
        default:
            printf("Père avec pid : %d\n", getpid());
            break;
    }

    return 0;
}