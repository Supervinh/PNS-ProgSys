/*
 *
 * Boucle du shell
 *
 * Erick Gallesio (1992-12-08)
 * Stéphane Lavirotte (2017/04/04)
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>

#define CMD_MAX_LEN 1024

jmp_buf buff;

void handler(int signal)
{
    printf("\n**Signal SIGINT reçu (signal=%d)**\n", signal);
	printf("Faire ^D pour quitter le shell\n");
    fflush(stdout);
    siglongjmp(buff, 1);
}

void prompt()
{
    printf("$ ");
    fflush(stdout);
}

int main()
{
    char cmd[CMD_MAX_LEN];
    int n;
    struct sigaction sigact;
    sigset_t sigmask;

	/* Configure l'action sur le signal */
    sigact.sa_handler = handler;
    sigact.sa_mask = sigmask;
    sigact.sa_flags = SA_ONSTACK; /* Permet d'éviter un débordement de pile à l'exécution du handler trouvé dans le cas Ubuntu 14.04 32 bits et Debian 7 32 bits */

    sigsetjmp(buff, 1);
    
	sigaction(SIGINT, &sigact, NULL);
    //signal(SIGINT, handler);

    while (1) {
        prompt();
        if (!(n = read(0, cmd, CMD_MAX_LEN)))   /* fin de fichier ==> terminer */
            break;
        cmd[n] = '\0';
        system(cmd);
    }
    return 0;
}

