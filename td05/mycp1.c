#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

int main(int argc, char *argv[]) {
    if (argc == 3) {
        char buffer[512];
        int n;
        int fdin = open(argv[1], O_RDONLY);
        int fdout = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR|S_IWUSR);
        while ((n = read(fdin, buffer, 512)) != 0) {
            write(fdout, buffer, n);
        }
        close(fdin);
        close(fdout);
    }
    else {
        for (int i = 1; i < argc - 1; i++) {
            char *buffer = malloc(512);
            int n = 0;
            int fdin = open(argv[i], O_RDONLY);
            char *dest = malloc(512);
            strcat(dest, argv[argc - 1]);
            strcat(dest, "/");
            strcat(dest, basename(argv[i]));
            int fdout = open(dest, O_WRONLY | O_CREAT, S_IRUSR|S_IWUSR);
            while ((n = read(fdin, buffer, 512)) != 0)
                write(fdout, buffer, n);
            close(fdin);
            close(fdout);
            dest = NULL;
            buffer = NULL;
        }
    } 
}