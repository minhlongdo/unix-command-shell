#include "init/init.h"
#include "util/util.h"
#include "datastructure/env.h"

int main(int argc, char** argv) {

  EnvVariable* env = (EnvVariable*)malloc(sizeof(EnvVariable));
  init(&env);

  /* Debugging information.
  printf("Starting Unix Command Shell.\n");
  printf("HOME: %s",env->home);
  printf("PATH: %s",env->path);
  */

  /* Terminal execution loop */
  terminal_main(&env);
  /* Print {directory}>
  printf("%s>", dir);
  scanf("%s", cmd);
  printf("Entered command: %s\n", cmd);
  */
  /* Read command */
  /* Parse command */
  /* Conditional executions */
  /* Check for child process etc. */
  /* Repeat until exit entered */

  /* Free memory */
  free(env);

  return 0;
}
