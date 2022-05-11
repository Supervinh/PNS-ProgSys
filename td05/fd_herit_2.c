#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <dirent.h>

char msg_parent[] = "Parent\n";
char msg_child[] = "Child\n";

int main()
{
    int fd;
    DIR *dirp;
    struct dirent *dentry;

    if ((dirp = opendir(".")) == NULL)
        perror("opendir()");

    fd = open("foo", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    write(fd, "Pere avant fork\n", 20);

    switch (fork()) {
    case -1: 
        perror("fork");
        abort();
    case 0: 
        if ((dentry = readdir(dirp)) == NULL)
            perror("readdir()");
        else
            printf("Lu correctement répertoire \"%s\"\n", dentry->d_name);

        write(fd, msg_child, strlen(msg_child));

        sleep(2);

        write(fd, msg_child, strlen(msg_child));

        exit(0);

    default: 
        sleep(1);

        write(fd, msg_parent, strlen(msg_parent));
        printf("Imprimer le contenu du fichier foo\n");

        wait(NULL);
    }
}


