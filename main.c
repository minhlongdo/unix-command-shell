#include "init/init.h"
#include "datastructure/env.h"

int main(int argc, char** argv) {

  EnvVariable* env = (EnvVariable*)malloc(sizeof(EnvVariable));
  char* cmd = (char*)malloc(sizeof(char)*256);
  char* dir = (char*)malloc(sizeof(char)*1024);
  init(&env);

  while(1) {
    get_current_dir(&dir);
    printf("%s>", dir);
    fgets(cmd, 256, stdin);

    memset(dir, '\0', strlen(dir));
    memset(cmd, '\0', strlen(cmd));
  }

  /* Free memory */
  free(env);
  free(cmd);

  return 0;
}
