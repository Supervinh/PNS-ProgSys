#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 5

void *func(void *arg) {
    sleep(1 + rand() % 5);
    long n = (long *) arg;
    printf("Dans le thread #%ld\n", n);
    return NULL;
}

int main() {
    long i;
    pthread_t threads[MAX];

    /* Creation des threads */
    for (i = 0; i < MAX; i++) {
        pthread_create(&threads[i], NULL, func, (void *) i);
    }

    /* On attend que ça se termine */
    for (long j = 0; j < MAX; j++) {
        pthread_join(threads[j], NULL);
    }

    return 0;
}
