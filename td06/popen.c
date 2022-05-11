#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>
#include <stdio.h>
#include <wait.h>

int lecture(int f){
    char buf[1];
    int i;
    int res=0;
    while((i = read(f,buf,1)) > 0 )
        res+=i;
    close(f);
    return res;
}

int mypopen(char *argv[]){
    int tube[2];
    pipe(tube);
    switch (fork())
    {
    case -1:
        perror("Erreur fork");
        abort();
    case 0:
        close(tube[0]);
        dup2(tube[1],STDOUT_FILENO);
        execvp(argv[1],argv+1);
        break;
    default:
        close(tube[1]);
        wait(NULL);
    }
    return tube[0];
}

int main(int argc, char *argv[]) {
    if(argc<3)
        exit(1);
    printf("Nombre total de caractères lus : %d\n",lecture(mypopen(argv)));
    return 0;
}