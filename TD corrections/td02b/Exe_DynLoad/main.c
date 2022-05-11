#include <Windows.h>
#include <stdio.h>

// décrire le prototype de la procédure 
typedef void(* proto_PrintStop) (char*);

int main()
{
	proto_PrintStop PrintStop = NULL;

	// Attention : le chemin du fichier est en Unicode si votre projet est configuré comme tel, la chaine doit alors être L" "
	void * hinstDLL = LoadLibrary("Bibliotheques.dll");
	if (!hinstDLL) {
		// Erreur lors du chargement de la bibliothèque ?
		printf("Impossible de charger la bibliothèque.");
	}
	else {
		// On récupère l'adresse de la fonction
		PrintStop = (proto_PrintStop)GetProcAddress(hinstDLL, "PrintStop");
	}
	char a[] = "test";
	PrintStop(a);
	FreeLibrary(hinstDLL);

	//PrintStop(a); // qu'arrive-t'il  ?
}


