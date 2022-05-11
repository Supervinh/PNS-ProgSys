/* ---------------------------------------------------------------------------------
 * Primitives de POSIX.1 : Signaux
 * ---------------------------------------------------------------------------------
 * Jean-Paul Rigault (2005/04/12)
 * Stéphane Lavirotte (2018/04/14)
 * ---------------------------------------------------------------------------------
 * Capture de signaux avec signal()
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

    /* Réarmement du handler dans le cas d'une compilation ANSI C (-ansi)
	 * On n'a pas besoin de réarmer sur SIGSEGV car est déjà sorti */
    /*signal(SIGINT,  on_sig);*/
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
    /* Mise en place des pièges à signaux */
    signal(SIGINT, on_sig);
    signal(SIGSEGV, on_sig);
		    
    /* On met le programme en attente : attention, sleep() ne conviendrait pas
     * ici (essayez, vous verrez... et lisez la page de man de sleep())
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
