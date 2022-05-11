#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int my_system(const char *cmd) {
     
    int stat;

    switch (fork()) {
        case -1 :
            perror("fork");
            exit(1);
        case 0 :
            execl("/bin/sh", "sh", "-c", cmd, NULL);
        default:
            wait(&stat);
        return stat;
    }
}

int main(){
   char variable[100];
    while(1){
        gets(variable);
        my_system(variable);
    }
    return 0;
}

