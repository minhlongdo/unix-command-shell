#include "init/init.h"
#include "util/util.h"
#include "datastructure/env.h"

int main(int argc, char** argv) {

  EnvVariable* env = (EnvVariable*)malloc(sizeof(EnvVariable));
  char c;
  char* cmd = (char*)malloc(sizeof(char)*100);
  char* path_str = (char*)malloc(sizeof(char)*256);
  char* tmp = (char*)malloc(sizeof(char)*100);
  char* dir = current_dir();
  init(&env);
  printf("Starting Unix Command Shell.\n");
  printf("HOME: %s",env->home);
  printf("PATH: %s",env->path);
  printf("Current: %s\n", dir);

  /* Print {directory}>*/
  /* Read command */
  /* Parse command */
  /* Conditional executions */
  /* Check for child process etc. */
  /* Repeat */

  /* Free memory */
  free(env);
  free(cmd);
  free(tmp);
  free(path_str);

  return 0;
}
