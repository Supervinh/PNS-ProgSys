#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "load_library.h"

static void *oplib = NULL;
static void (*sort_handler)(int [], int);

void load_library(const char *library_name) {
    oplib = dlopen(library_name, RTLD_LAZY);
    if (oplib != NULL) sort_handler = (void (*)(int [], int))dlsym(oplib, "sort");
    else (printf ("Erreur, lib NULL"));
}

void sort(int tab[], int size) {
    sort_handler(tab, size);
}

void unload(){
    if (oplib != NULL) dlclose(oplib);
    else (printf("Erreur, lib NULL"));
}