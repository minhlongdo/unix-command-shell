#include "init/init.h"
#include "datastructure/env.h"

int main(int argc, char** argv) {

  EnvVariable* env = (EnvVariable*)malloc(sizeof(EnvVariable));
  init(&env);

  printf("PATH: %s", env->path);
  printf("HOME: %s", env->home);

  /* Free memory */
  free(env);

  return 0;
}
