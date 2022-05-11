/* ---------------------------------------------------------------------------------
 * Primitives de POSIX.1 : Signaux
 * ---------------------------------------------------------------------------------
 * Jean-Paul Rigault (2005/04/12)
 * Stéphane Lavirotte (2017/04/04)
 * ---------------------------------------------------------------------------------
 * Capture de signaux et execXX() : programme à exécuter
 * ---------------------------------------------------------------------------------
 */
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc >= 1) {
		printf("Début de %s\n", argv[0]);
		sleep(5);
		printf("Fin de %s\n", argv[0]);
		return 0;
	}
}
