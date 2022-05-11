#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "util.h"

int main()
{
    int file = open("Vinh_Faucher_TD05.txt",O_RDONLY);
    struct dirent *dentry;
                DIR *dirp = opendir(".vscode");
                if (dirp == NULL) {
                    perror("Erreur chargement du dossier\n");
                    exit(1);
                }
    switch(fork()){
        case 0:
            {char path[49];
            read(file,path,49 * sizeof(char));
            printf("Fichier : %s\n\nDossier :\n",path);

            while ((dentry = readdir(dirp)) != NULL) {
                        printf("%s\n", dentry->d_name);
                }
            close(file);
            exit(0);}
        default:
            exit(0);
    }
    return 0;
}