#include "init/init.h"
#include "util/util.h"
#include "datastructure/env.h"

int main(int argc, char** argv) {

  Terminal* terminal = (Terminal*)malloc(sizeof(Terminal));
  terminal->env = (EnvVariable*)malloc(sizeof(EnvVariable));
  printf("Starting Unix Command Shell.\n");
  read_env_val("profile", &terminal);

  printf("PATH: %s\n", (terminal->env)->path);
  printf("HOME: %s\n", (terminal->env)->home);

  /* Free memory */
  free(terminal->env);
  free(terminal);

  return 0;
}
