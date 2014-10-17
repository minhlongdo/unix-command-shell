#include "init/init.h"
#include "util/util.h"
#include "datastructure/env.h"

int main(int argc, char** argv) {

  EnvVariable* env = (EnvVariable*)malloc(sizeof(EnvVariable));
  init(&env);
  printf("Starting Unix Command Shell.\n");
  printf("HOME: %s",env->home);
  printf("PATH: %s",env->path);

/*
  while(1) {
    char* input;

    /* parsing command and execute */
    /*
    command_parser(input, &terminal)
    */

    /* Break from while loop */
    /*
    if(strcmp(input,"exit")) {
      break;
    }
  }
  */
  /* Free memory */
  free(env);

  return 0;
}
