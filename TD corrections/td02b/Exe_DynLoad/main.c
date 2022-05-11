#include <Windows.h>
#include <stdio.h>

// d�crire le prototype de la proc�dure 
typedef void(* proto_PrintStop) (char*);

int main()
{
	proto_PrintStop PrintStop = NULL;

	// Attention : le chemin du fichier est en Unicode si votre projet est configur� comme tel, la chaine doit alors �tre L" "
	void * hinstDLL = LoadLibrary("Bibliotheques.dll");
	if (!hinstDLL) {
		// Erreur lors du chargement de la biblioth�que ?
		printf("Impossible de charger la biblioth�que.");
	}
	else {
		// On r�cup�re l'adresse de la fonction
		PrintStop = (proto_PrintStop)GetProcAddress(hinstDLL, "PrintStop");
	}
	char a[] = "test";
	PrintStop(a);
	FreeLibrary(hinstDLL);

	//PrintStop(a); // qu'arrive-t'il  ?
}


