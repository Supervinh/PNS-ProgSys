#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int tube = open(argv[1], O_RDONLY);
    char buff[1000];
    while (read(tube, buff, 1000)) {
        printf("%s\n", buff);
    }
    close(tube);

    return 0;
}