/* ---------------------------------------------------------------------------------
 * Primitives de POSIX.1 : Signaux
 * ---------------------------------------------------------------------------------
 * Jean-Paul Rigault (2005/04/12)
 * Stéphane Lavirotte (2017/04/04)
 * ---------------------------------------------------------------------------------
 * Capture de signaux et execXX()
 * ---------------------------------------------------------------------------------
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

/* Une fonction qui crée un fils exécutant le programme tst_exec_signal-aux.exe et lui envoit SIGINT */
void Exec()
{
    pid_t pid;

    if ((pid = fork()) != 0)
    {
        /* Père */
        /* On attent que le fils démarre */
        sleep(1); 
		/* On lui envoie le signal SIGINT et on l'attend */
        kill(pid, SIGINT);
        wait(NULL);
    }
    else 
    {
        /* Fils */
        execl("./tst_exec_signal-aux.exe", "tst_exec_signal-aux.exe", NULL);
        perror("exec");
        exit(0);
    }
}

void on_int(int sig)
{
    printf("signal %d\n", sig);
}

int main()
{
    struct sigaction sigact;
    sigset_t sigmask;
	
    sigact.sa_handler = SIG_IGN;
    sigact.sa_mask = sigmask;
    sigact.sa_flags = SA_ONSTACK; /* Permet d'éviter un débordement de pile à l'exécution du handler trouvé dans le cas Ubuntu 14.04 32 bits et Debian 7 32 bits */

    printf("Le père ignore SIGINT: le fils doit aller jusqu'au bout (5 secondes)\n");
	//signal(SIGINT, SIG_IGN);
    sigaction(SIGINT, &sigact, NULL);

    Exec();

    printf("Le père trappe SIGINT: le fils meurt (signal rétabli à l'action par défaut)\n");
    //signal(SIGINT, on_int);
    sigact.sa_handler = on_int;
	sigaction(SIGINT, &sigact, NULL);

    Exec();

    printf("Le père remet SIGINT à l'action par défaut : le fils meurt immédiatement\n");
    sigact.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sigact, NULL);
    signal(SIGINT, SIG_DFL);

    Exec();

    return 0;    
}
