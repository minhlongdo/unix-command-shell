#include "init/init.h"
#include "datastructure/env.h"

int main(int argc, char** argv) {

  EnvVariable* env = (EnvVariable*)malloc(sizeof(EnvVariable));
  char* cmd = (char*)malloc(sizeof(char)*256);
  char* dir = (char*)malloc(sizeof(char)*1024);

  init(&env);

  /* Clear terminal */
  system("clear");
  
  while(1) {
    get_current_dir(&dir);
    printf("%s>", dir);
    fgets(cmd, 256, stdin);

    /* Strip traling newline */
    cmd[strlen(cmd)-1] = '\0';

    //printf("Command: %s\n", cmd);

    /* Exit program */
    if (strcmp(cmd, "exit") == 0)
      break;

    char* strArray[40];
    int args_count = 0;

    if(strstr(cmd, " ") != NULL) {
      char* token = strtok(cmd, " ");
      /* Tokenize command */
      while(token != NULL) {
        strArray[args_count] = (char*)malloc(sizeof(char)*strlen(token));
        strcpy(strArray[args_count], token);
        printf("[%s] -> %i\n", token, strlen(strArray[args_count]));
        token = strtok(NULL, " ");
        args_count++;
      }
    } else {
      strArray[args_count] = (char*)malloc(sizeof(char)*strlen(cmd));
      strcpy(strArray[args_count],cmd);
    }
    char* bin_dir;
    /* Search for command */
    printf("Array content - Command: %s\n", strArray[0]);
    int retval = search_bin(&strArray[0], &env, &bin_dir);

    memset(dir, '\0', strlen(dir));
    memset(cmd, '\0', strlen(cmd));
    args_count--;
    while(args_count > -1) {
      free(strArray[args_count]);
      args_count--;
    }
  }

  /* Free memory */
  free(env);
  free(cmd);
  free(dir);

  return 0;
}
