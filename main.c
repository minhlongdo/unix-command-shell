#include "init/init.h"
#include "util/util.h"
#include "datastructure/env.h"

int main(int argc, char** argv) {

  Terminal* terminal = (Terminal*)malloc(sizeof(Terminal));
  terminal->env = (EnvVariable*)malloc(sizeof(EnvVariable));
  printf("Starting Unix Command Shell.\n");
  init(&terminal);

  printf("PATH: %s", (terminal->env)->path);
  printf("HOME: %s", (terminal->env)->home);
  printf("Current dir: %s", terminal->cur_dir);

  /* Free memory */
  free(terminal->env);
  free(terminal);

  return 0;
}
