#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "util.h"


void print_fileinfo(char *file){
    printf("%s\n", file);
}

void list(char *path) {
    if (!is_dir(path)) {
        print_fileinfo(path);
        exit(0);
    }
    DIR *dir = opendir(path);
    if (!dir) {
        perror("Erreur chargement du dossier\n");
        exit(1);
    }


    struct dirent *dirent;
    char newdir[512];
    printf("\nCurrent directory: %s\n", path);
    while ((dirent = readdir(dir))) {
        if (!is_dot_dir(dirent->d_name)) {
            print_fileinfo(dirent->d_name);
        }
    }
    closedir(dir);

    dir = opendir(path);

    while ((dirent = readdir(dir))) {
        if (!is_dot_dir(dirent->d_name)) {
            if (dirent->d_type == 4) {
                sprintf(newdir, "%s/%s", path, dirent->d_name);
                list(newdir);
            }
        }
    }
    closedir(dir);
}


int main(int argc, char *argv[]) {
    switch (argc) {
        case 1:;
            char tab[1024];
            getcwd(tab, sizeof(tab));
            printf("Dossier : %s", tab);
            list(tab);
            break;
        case 2:
            printf("Dossier demandé: %s\n", argv[1]);
            list(argv[1]);
            break;
        default:
            break;
    }
    return 0;
}