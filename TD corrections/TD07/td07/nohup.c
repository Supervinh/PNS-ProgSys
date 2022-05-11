/*
 * nohup.c	-- commande nohup
 *
 * Erick Gallesio (2014/04/07)
 * Stéphane Lavirotte (2017/04/04)
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd;

    if (argc == 1) {
        fprintf(stderr, "Usage: %s command arg ...\n", *argv);
        exit(1);
    }

    fd = open("./nohup.out", O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd < 0) {
        perror(*argv);
        exit(1);
    }

    /* Redirections */
    close(1);
    dup(fd);
    close(2);
    dup(fd);
    close(fd);

    struct sigaction sigact;
    sigset_t sigmask;

	/* Configure l'action sur le signal */
    sigact.sa_handler = SIG_IGN;
    sigact.sa_mask = sigmask;
    sigact.sa_flags = SA_ONSTACK; /* Permet d'éviter un débordement de pile à l'exécution du handler trouvé dans le cas Ubuntu 14.04 32 bits et Debian 7 32 bits */

 /* S'immuniser contre SIGHUP */
	sigaction(SIGHUP, &sigact, NULL);
    //signal(SIGHUP, SIG_IGN);

    /* Lancer le programme */
    execvp(argv[1], argv + 1);
    perror("exec"); /* affiché si exec échoue seulement */

    return 0; /* pour GCC seulement */
}

