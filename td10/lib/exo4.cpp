#include "exo4.h"
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>

JNIEXPORT jint JNICALL Java_exo4_getPid(JNIEnv *env, jclass cls) {
    return getpid();
}

JNIEXPORT jlong JNICALL Java_exo4_pfork(JNIEnv *env, jclass cls) {
	return(fork());
    
}

JNIEXPORT void JNICALL Java_exo4_pexit(JNIEnv *env, jclass cls, jint n) {
    exit(n);
}

JNIEXPORT jint JNICALL Java_exo4_psleep(JNIEnv *env, jclass cls, jint n) {
    return (jint) sleep(n);
}

JNIEXPORT jint JNICALL Java_exo4_pwait(JNIEnv *env, jclass cls) {
  return (jint) wait(NULL);
}