#include "init/init.h"
#include "util/util.h"
#include "datastructure/env.h"

int main(int argc, char** argv) {

  EnvVariable* env = (EnvVariable*)malloc(sizeof(EnvVariable));
  printf("Starting Unix Command Shell.\n");
  read_env_val("profile", &env);

  printf("PATH: %s\n", env->path);
  printf("HOME: %s\n", env->home);

  free(env);

  return 0;
}
