#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int aine, cadet;

void on_signal_cadet(int sig){
    printf("Reception du signal dans le fils cadet SIGUSR1 : %i\n", sig);
    printf("Envoie du signal SIGUSR2\n");
    kill(aine, SIGUSR2);
    printf("Fin du fils cadet\n");
    exit(0);
}

void on_signal_aine(int sig){
    printf("Reception du signal dans le fils ainé SIGUSR2 : %i\n", sig);
    printf("Fin du fils aine\n");
    exit(0);
}

int main()
{
    struct sigaction sigact;


    aine = fork();
    switch (aine){
        case -1: 
            perror("Fork");
            exit(0);

        case 0:
            sigact.sa_handler = on_signal_aine;
            sigaction(SIGUSR2, &sigact, NULL);
            while(1);
    }

    cadet = fork();
    switch (cadet){
        case -1: 
            perror("Fork");
            exit(0);
            
        case 0:
            sigact.sa_handler = on_signal_cadet;
            sigaction(SIGUSR1, &sigact, NULL);
            while(1);     
    }

    printf("Le parent envoie le signal\n");
    kill(cadet, SIGUSR1);
    wait(NULL);
    wait(NULL);
    return 0;
}
