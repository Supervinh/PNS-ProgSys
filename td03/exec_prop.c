#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

pid_t getpid(void);
pid_t getppid(void);

int main(){
    printf("Début %d\n", getpid());
    execlp("./exec_prop-aux.exe","exec_prop-aux", "coucou", NULL);
    printf("Ca doit pas apparaitre \n");
    return 0;
}