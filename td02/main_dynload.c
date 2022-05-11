#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "sort.h"
#include "utils.h"
#include "timer.h"
#include "load_library.h"
#include <dirent.h>

/* ------------------------------------------------------------------------------------
 * Valeurs par défaut des variables globales qui suivent 
 * ------------------------------------------------------------------------------------
 */

#define SIZE 10000
#define FALSE 0
#define TRUE 1

/* ------------------------------------------------------------------------------------
 * Variables globales 
 * ------------------------------------------------------------------------------------
*/

static int Size_Array = SIZE;
static int Verbose = FALSE;

/* ------------------------------------------------------------------------------------
 * Prototypes de fonctions définies plus tard 
 * ------------------------------------------------------------------------------------
*/
static void Scan_Args(int argc, char *argv[]);
static void Usage(const char *execname);

int Strstr(char big[], char small[]) {
  int i, s, b;

  for (i = 0; big[i]; i++) {
    for (s=0, b=i; small[s]; s++, b++) {
      if (small[s] != big[b]) break;
    }
    // Si on est arrivé au bout de small (i.e small[s] == '\0') on a trouvé
    if (small[s] == '\0') return 1;
  }

  // Si on est là, c'est qu'on a pas trouvé small dans big
  return 0;
}


int main(int argc, char *argv[])
{
    /* Décodage des arguments de la ligne de commande */
    Scan_Args(argc, argv);

    int list[Size_Array];

    // Initialize a ramdom list of numbers;
    srand(0);
    for (int i = 0; i < Size_Array; i++) {
        list[i] = rand() % 1000;
    }

	if (Verbose) {
		printf("Array to sort:");
		print_list(list, Size_Array);
	}
	
    struct dirent *dir;
    DIR *d = opendir(".");
    char *fichier;
    if (d)
    {
        while((dir = readdir(d)) != NULL){
            fichier = dir -> d_name;
            //printf("%s \n", fichier);
            if ((Strstr(fichier,".so"))==1){
                load_library(fichier);
                printf("Utilisation de %s \n", fichier);
                struct timespec vartime = timer_start();
                sort(list, Size_Array);
                long time_elapsed_nanos = timer_end(vartime);
                
                if (Verbose)
                    printf("Time taken for sorting (nanoseconds): ");
                printf("%ld\n", time_elapsed_nanos);

                if (Verbose) {
                    printf("Sorted array:");
                    print_list(list, Size_Array);
                    printf("\n");
	            }
                unload();    
            }
        }
        closedir(d);
    };
    
    
}

/* Analyse des arguments 
 * ----------------------
 */
static void Scan_Args(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
            case 'h':
                Usage(argv[0]);
                exit(1);
            case 's':
                Size_Array = atoi(argv[++i]);
                break;
			case 'v':
				Verbose = TRUE;
				break;
            }
        }else {
            load_library(argv[i]);
        }
    }
}

/* Information d'utilisation
 * -------------------------
 */
static void Usage(const char *execname)
{
    fprintf(stderr, "\nUsage: %s [options]\n", execname);
    fprintf(stderr, "\nOptions générales\n"
           "-----------------\n"
           "-h\tce message\n"
           "-s\ttaille du tableau à trier\n"
		   "-v\taffiche plus d'informations\n");
}

