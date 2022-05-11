#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <jni.h>

int main(){
    JavaVM *jvm;
  JNIEnv *env;
  JavaVMInitArgs vm_args = {
                            .version = JNI_VERSION_10,
                            .nOptions= 0,
                            .options = NULL,
                            .ignoreUnrecognized = false,
  };

  // load and initialize a Java VM, return a JNI interface  pointer in env
  int res = JNI_CreateJavaVM(&jvm, (void **) &env, &vm_args);
  if (res != 0) {
    fprintf(stderr, "Impossible de créer une JVM\n");
    exit(1);
  }
  jclass cls = env->FindClass("exo1");
  if (! cls) {
    fprintf(stderr, "Impossible de trouver la classe exo1\n");
    exit(1);
  }
  jmethodID mid = env->GetStaticMethodID(cls, "main", "([Ljava/lang/String;)V");
  if (! mid) {
     fprintf(stderr, "Cannot find method main of class Exo1\n");
    exit(1);
  }

  printf("C process ID: %d\n", getpid());
  env->CallStaticVoidMethod(cls, mid, NULL);

  printf("Retour à la JVM\n");
  printf("C process ID: %d\n", getpid());

  // Destrucytion de la JVM
  jvm->DestroyJavaVM();
  printf("Fin de la JVM\n");
  
  return 0;
}