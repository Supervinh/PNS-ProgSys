#include "exo2.h"
#include <stdio.h>
#include <unistd.h>

JNIEXPORT jint JNICALL Java_exo2_getPid(JNIEnv *env, jclass cls) {
    return getpid();
}
