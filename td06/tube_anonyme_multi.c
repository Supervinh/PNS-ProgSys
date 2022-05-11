#include <unistd.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>


void lecture(int fd) {
    char buff[3];
    while (read(fd, buff, 3)) {
        write(STDOUT_FILENO, buff, sizeof(buff));
        printf("\n");
    }
    printf("\n");
}

void writing(int p[2], char *buff, unsigned int sleep_timer) {
    for (int i = 0; i < 13; i++) {
        write(p[1], buff, 2);
        buff += 2;
        sleep(sleep_timer);
    }
}

int main() {
    int p[2];
    pipe(p);
    switch (fork())
    {
    case -1:
        perror("Erreur fork");
        abort();
    case 0:
        writing(p, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1);
        break;
    default:
        switch (fork())
        {
        case -1:
            perror("Erreur fork");
            abort();                    
        case 0:
            writing(p, "abcdefghijklmnopqrstuvwxyz", 2);
            break;
        default:
            close(p[1]);
            lecture(p[0]);
            close(p[0]);
            break;
        }
        
    }
    fflush(stdout);
    return 0;
}
