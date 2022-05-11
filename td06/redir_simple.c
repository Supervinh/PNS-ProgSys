#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    fd = open("foo",O_WRONLY|O_CREAT|O_TRUNC,
    S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    dup2(fd, 1);
    system("ls -l");
    close(fd);

    return 0;
}