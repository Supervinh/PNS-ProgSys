#include "exo3.h"
#include <stdio.h>
#include <unistd.h>

JNIEXPORT jint JNICALL Java_exo3_getPid(JNIEnv *env, jclass cls) {
    return getpid();
}

JNIEXPORT void JNICALL Java_exo3_createFork(JNIEnv *env, jclass cls) {
	pid_t f = fork();
    switch(f){
    	case -1:
    		perror("Erreur dans le fork");
    	case 0:
    		printf("Le fils\n");
    		return;
    	default:
    		//wait();
    		printf("Le père\n");
    		return;
    }
}