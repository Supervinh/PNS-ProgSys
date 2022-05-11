#include <unistd.h>
#include <fcntl.h>
#include <memory.h>


int main(int argc, char *argv[]) {
    int tube = open(argv[1], O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    char *a_ecrire = "Je ne suis pas un robot tniognreĝnirkqg \n vhenrpghnpe";
    write(tube, a_ecrire, strlen(a_ecrire));
    close(tube);

    return 0;
}