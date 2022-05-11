#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

pid_t getpid(void);
pid_t getppid(void);

int main(){
    switch (fork()) {
        case -1 :
            perror("fork");
            abort();
        case 0 :
            printf("Fils : \n");
            exit(0);
        default:
            sleep(2);
            printf("Père : \n");
            break;
    }
    return 0;
}