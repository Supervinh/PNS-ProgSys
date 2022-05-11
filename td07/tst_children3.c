#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int aine,cadet;

void sign(int s){
    printf("Reception de %d ",s);
    if(s == SIGUSR1){
        printf("dans le cadet \n");
        kill(aine, SIGUSR2);
    }
    if(s == SIGUSR2)
        printf("dans l'ainé \n");
}

int main() {
    struct sigaction sigact;
    sigact.sa_handler = sign;
    switch (aine = fork())
    {
    case -1: 
        perror("Fork");
        exit(0);
    case 0:
        sigaction(SIGUSR2, &sigact, NULL);
        pause();
        printf("signal SIGUSR1 recu\n");
        exit(0);
    default:
        switch (cadet = fork())
        {
        case -1: 
            perror("Fork");
            exit(0);
        case 0:
            sigaction(SIGUSR1, &sigact, NULL);
            pause();
            printf("signal SIGUSR2 recu\n");
            exit(0);
        default:
            printf("Le parent envoie le signal au cadet %d\n",cadet);
            kill(cadet, SIGUSR1);
            wait(NULL);
            wait(NULL);
            printf("le pere a fini\n");
            exit(0);
        }
    }
    
}