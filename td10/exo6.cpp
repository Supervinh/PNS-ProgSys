#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <jni.h>

int main(int argc, char *argv[]) {
  printf("ID du processus en cours en c (avant le execlp): %d\n", getpid());
  execlp("java", "java", "Exo1", NULL);
  printf("D du processus en cours en c(après execlp): %d\n", getpid());
  printf("On ne peut pas voir ces messages après le execlp\n");
  printf("Au revoir");
  
  return 0;
}