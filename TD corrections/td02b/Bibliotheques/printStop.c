#include <stdio.h>

#define DLLEXPORT _declspec(dllexport)

DLLEXPORT void PrintStop(char*);

void PrintStop(char* lpszMsg)
{
	printf("%s\n", lpszMsg);
	getchar();
}