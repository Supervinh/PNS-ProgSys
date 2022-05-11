#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

void *print_thread(void *arg) {
    for (int i = 0; i < 5; i++) {
        printf("PID du thread : %d\n", (int)getpid());
        printf("Identifiant thead Unix : %lu\n", pthread_self());
        if (*(int *) arg > 0) sleep(*(int *) arg);
    }
    printf("Linux Thread ID: %ld\n", syscall(SYS_gettid));
    if (*(int *) arg<0) pthread_exit((void *)1);
    pthread_exit((void *)0);
}

int main(int argc, char *argv[]) {
    printf ("PID : %d\n", (int)getpid ()); 
    int n1 = 0;
    int n2 = 0;
    if (argc == 3) {
        n1 = atoi(argv[1]);
        n2 = atoi(argv[2]);
    }
    pthread_t t1, t2;

    long retour1, retour2;

    pthread_create(&t1,NULL,print_thread,&n1);

    pthread_create(&t2,NULL,print_thread,&n2);

    pthread_join(t1, (void*) &retour1);
    pthread_join(t2, (void*) &retour2);

    printf("Après exécution de thread 1: %ld\n", retour1);
    printf("Aprés exécution de thread 2: %ld\n", retour2);

    printf("Fin\n");

    return 0;
}