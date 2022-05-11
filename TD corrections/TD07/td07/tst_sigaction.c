/* ---------------------------------------------------------------------------------
 * Primitives de POSIX.1 : Signaux
 * ---------------------------------------------------------------------------------
 * Jean-Paul Rigault (2005/04/12)
 * Stéphane Lavirotte (2018/04/14)
 * ---------------------------------------------------------------------------------
 * Capture de signaux avec sigaction()
 * ---------------------------------------------------------------------------------
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>

/*
 * Fonction de capture des signaux (handler)
 * -----------------------------------------
 */
void on_sig(int sig)
{
    static int count = 0;

    switch (sig) {
    case SIGSEGV:
        printf("Signal capturé : SIGSEGV\n");
        /* Que faire d'autre que terminer ? */
        exit(1);
    case SIGINT:
        printf("Signal capturé : SIGINT\n");
        if (++count == 5) {
            printf("Reçu SIGINT 5 fois\n");
            exit(1);
        }
        break;
    default:
        /* Impossible de passer ici */
        assert(0);
        break;
    }
}

/* Programme principal
 * -------------------
 * Si ce programme est lancé en background, il est immunisé contre les signaux
 * émis par des caractères spéciaux au terminal (mais pas contre ceux
 * provenant de kill explicites (faits par exemple dans une autre fenêtre
 * xterm).
 */
int main()
{
    struct sigaction sigact;
    sigset_t sigmask;

    /* Mise en place du piège à signaux */
    sigemptyset(&sigmask);
    sigact.sa_handler = on_sig;
    sigact.sa_mask = sigmask;
    sigact.sa_flags = SA_ONSTACK; /* Permet d'éviter un débordement de pile à l'exécution du handler trouvé dans le cas Ubuntu 14.04 32 bits et Debian 7 32 bits */
    sigaction(SIGINT, &sigact, NULL);
    sigaction(SIGSEGV, &sigact, NULL);

    /* On met le programme en attente : attention, sleep() ne conviendrait pas
     * ici (essayez, vous verrez et lisez la page du manuel de sleep (man 3 sleep).
     */
    printf("Faites\n"
           "\t- 5 SIGINT pour arrêter le programme\n"
           "\t\tsoit '^C' au terminal, si lancement en avant-plan\n"
           "\t\tsoit 'kill -INT %d', si lancement en arrière-plan\n"
           "\t- envoyez des SIGSEGV (kill -SEGV %d)\n", getpid(), getpid());
    while (1) {}

    /*
     * Si on remplace la boucle infinie précédente par l'appel ci-dessous de
     * sleep(), le premier SIGINT est bien trappé mais on ne revient pas
     * terminer le sleep(). Voir la page du manuel (man 3 sleep).
     */
    /*sleep(5);*/

    /* Fin du programme (jamais atteinte en fait avec le while) */
    return 0;
}
