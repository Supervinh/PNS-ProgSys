#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>

int aine;
int cadet;

void on_sigusr1(int sig)
{
    if(sig == SIGUSR1){ 
        printf("Fils cadet reçoit SIGUSR1, envoit SIGUSR2 à son ainé et se termine\n");
        kill(aine, SIGUSR2);  
    }
    exit(0); 
}

void on_sigusr2(int sig)
{
    if(sig == SIGUSR2){
        printf("Fils ainé reçoit SIGUSR2 et se termine\n");
    }
    exit(0);
}

int main(){
    struct sigaction sigact1;
    struct sigaction sigact2;
    sigset_t sigusr1_mask;
    sigset_t sigusr2_mask;

    sigemptyset(&sigusr1_mask);
    sigemptyset(&sigusr2_mask);

    switch (aine = fork())
    {
    case -1:
        perror("Erreur Fork");
        abort();
    case 0:   
        printf("Ainé : %d\n", getpid());
        sigact2.sa_handler = on_sigusr2;
        sigact2.sa_mask = sigusr2_mask;
        sigaction(SIGUSR2, &sigact2, NULL);
        printf("Ainé en attente\n");    
        sleep(3);
        exit(0);
    default:
        switch (cadet = fork())
        {
        case -1:
            perror("Erreur Fork");
            abort();
        case 0:	 
            printf("Cadet : %d\n", getpid());
            sigact1.sa_handler = on_sigusr1;
            sigact1.sa_mask = sigusr1_mask;
            sigaction(SIGUSR1, &sigact1, NULL);
            printf("Cadet en attente\n");    
            sleep(3);
            exit(0);
            break;
        }
        break;
    }

    sleep(2); 

    printf("Père envoie un signal au fils cadet\n");    
    kill(cadet, SIGUSR1);

    wait(0);
    wait(0);	
    return 0;
}
