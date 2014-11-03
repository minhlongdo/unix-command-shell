#include "init/init.h"
#include "util/util.h"
#include "datastructure/env.h"
#include "built-in/builtin.h"

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
    else if(strcmp(cmd, "clear") == 0)
      system("clear");
    else if (strstr(cmd, "$HOME=") != NULL) {
      /* Check if the fist characters are correct */
      char* home = "$HOME=";
      int i = 0;
      for(i=0;i<strlen(home);i++) {
        if(cmd[i] != home[i])
          i = -1;
          break;
      }
      if (i != -1) {
        /* Replace environment variable HOME value */
        int len = strlen(cmd) - strlen(home);
        char* env_val = (char*)malloc(sizeof(char)*len + 1);
        strcpy_range(&env_val, &cmd, strlen(home), strlen(cmd));
        change_env_var(&env, &home, &env_val);

        free(env_val);
        printf("Current HOME: %s\n", env->home);
        printf("Current PATH: %s\n", env->path);
      }

    } else if (strstr(cmd, "$PATH=") != NULL) {
      /* Check if the fist characters are correct */
      char* path = "$PATH=";
      int i = 0;
      for(i=0;i<strlen(path);i++) {
        if(cmd[i] != path[i])
          i = -1;
          break;
      }
      if (i != -1) {
        /* Replace environment variable PATH value */
        int len = strlen(cmd) - strlen(path);
        //printf("PATH value length: %i\n", len);
        //printf("Length of $PATH=: %i\n", strlen(path));
        char* env_val = (char*)malloc(sizeof(char)*len + 2);
        strcpy_range(&env_val, &cmd, strlen(path), strlen(cmd));
        change_env_var(&env, &path, &env_val);

        free(env_val);
        //printf("Current HOME: %s\n", env->home);
        //printf("Current PATH: %s\n", env->path);
      }
    }
    else {
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
        args_count++;
        strArray[args_count] = NULL;
      }

      /* Check for builtin functions */
      if (strcmp(strArray[0], "cd") == 0) {
        if (args_count > 2) {
          perror("Too many arguments");
        } else if(args_count == 1) {
          /* Change to default director */
          change_dir(&strArray[1], &env);
        } else if(args_count == 2) {
          /* Change to another specified dir */
          change_dir(&strArray[1], &env);
        } else {
          printf("Number of args: %i\n", args_count);
          /* Unexpected error */
          perror("Unexpected error.");
          /* Free memory */
          args_count--;
          while(args_count > -1) {
            free(strArray[args_count]);
            args_count--;
          }
          break;
        }
      } else {
        char* bin_dir;
        /* Search for command */
        //printf("Array content - Command: %s\n", strArray[0]);
        int retval = search_bin(&strArray[0], &env, &bin_dir);
        printf("Binary path: %s\n", bin_dir);

        int i=0;
        int length = 0;
        for(i=0;i<args_count;i++)
          length = length + strlen(strArray[i]);

        printf("Total length: %i\n", length);

        char* command = (char*)malloc(sizeof(char)*(length + 1 + (length - 1)));

        if(command == NULL)
          perror("Unable to allocate memory.\n");

        strcpy(command, bin_dir);
        printf("Current command: %s\n", command);
        for(i=1;i<args_count;i++) {
          strcat(command, " ");
          strcat(command, strArray[i]);
        }

        printf("End command: %s\n", command);


        int status = sys_call(&bin_dir, &command);
        if (status == 0)
          printf("Success.\n");
        else if (status == -1)
          printf("Failure.\n");

        free(bin_dir);
        free(command);
      }

      /* Free memory */
      args_count--;
      while(args_count > -1) {
        free(strArray[args_count]);
        args_count--;
      }
    }

    memset(dir, '\0', strlen(dir));
    memset(cmd, '\0', strlen(cmd));
  }

  /* Free memory */
  free(env);
  free(cmd);
  free(dir);

  return 0;
}
