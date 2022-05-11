#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h> 
#include <stdlib.h> 


#define NB_PROCESS 10
#define NB_LOOP 10

pid_t getpid(void);
pid_t getppid(void);

int main(){
    int i = 0;

    for(; i < NB_PROCESS; i++){
        switch (fork()) {
            case -1 :
                perror("fork");
                exit(1);
            case 0 :
                for(int j = 0; j < NB_LOOP; j++){
                    printf("%d\n", i);
                    sleep(1);
                }
                exit(0);
            default:
                break;
        }
    }

    /* Mesure de salubrité sociale, le père attend la fin de tous ses fils */
    for (i = 0; i < NB_PROCESS; ++i) wait(0);

    /* évite le problème d'affichage à la sortie */
    fflush(stdout);

    return 0;
}