#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include<sys/wait.h>

void on_signal(int sig) {
    printf("*** signal %d\n", sig);
}

int main() {
    int pid1;
    int pid2;
    struct sigaction sigact_cadet, sigact_aine;
    sigset_t msk_cadet, msk_aine;

    switch (pid1 = fork()) {
        case -1:
            perror("error in 1st fork");
            exit(1);

        case 0:
            printf("fils1\n");
            sigact_aine.sa_handler = on_signal;
            sigact_aine.sa_mask = msk_aine;
            sigaction(SIGUSR2, &sigact_aine, NULL);
            sleep(1);
            exit(0);
        default:
            switch (pid2 = fork()) {
                case -1:
                    perror("error in 2nd fork");
                    exit(1);
                case 0:
                    printf("fils2\n");
                    sigact_cadet.sa_handler = on_signal;
                    sigact_cadet.sa_mask = msk_cadet;
                    sigaction(SIGUSR1, &sigact_cadet, NULL);
                    sleep(1);
                    kill(pid1, SIGUSR2);
                    exit(0);

                default:
                    break;

            }
    }

    printf("parent\n");
    sleep(1);
    kill(pid2, SIGUSR1);
    wait(0);
    wait(0);
}