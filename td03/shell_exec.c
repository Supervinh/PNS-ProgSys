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
            exit(1);
        case 0 :
            execlp("/bin/who","who",NULL);
        default:
            wait(NULL);
            execl("/bin/ls", "ls","-ls",getenv("HOME"), NULL);
            break;
    }
    return 0;
}