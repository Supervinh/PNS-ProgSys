#include <sys/param.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int consecutif;
void on_signal(int sig) {
    printf("*** signal %d\n", sig);
    if (sig == 2) {
        consecutif++;
        if (consecutif==5) exit(1);
        signal(SIGINT, on_signal);
    }
    else {
        consecutif = 0;
        signal(SIGSEGV, on_signal);
    }
}


int main() {
    consecutif = 0;
    signal(SIGSEGV, on_signal);
    signal(SIGINT, on_signal);
    while (1) {
        pause();
    }
    /*int  s = sleep(10);
    printf("%d\n", s);*/
}