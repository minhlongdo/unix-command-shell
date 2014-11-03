#include "util.h"

/**
 * Execute program with its given arguments.
 *
 * @param bin_cmd Location of binary executable.
 * @param args Arguments for the program.
 * @return status 0 for success and -1 for fail. 
 */
int sys_call(char** bin_cmd, char** args) {

  char* args_command = (char*)malloc(sizeof(char)*strlen(*args));
  strcpy(args_command, *args);
  //remove_str(&(*bin_cmd), &(*args), &args_command);
  printf("Arguments: %s\n", args_command);

  int status = 0;
  pid_t pid;

  char *paramList[40];
  int i=0;
  char *token = strtok(args_command, " ");

  while(token != NULL) {
    paramList[i] = (char*)malloc(sizeof(char)*strlen(token));
    strcpy(paramList[i], token);
    printf("%s -> %s\n", token, paramList[i]);
    token = strtok(NULL," ");
    printf("Token: %s\n", token);
    i++;
  }
  printf("Number of iterations: %i\n", i);
  paramList[i] = NULL;

  pid = fork();
  if (pid == 0) {
    if(i <= 1)
      execl(*bin_cmd, *args, NULL);
    else if (i > 1)
      execv(*bin_cmd, paramList);
    _exit(EXIT_FAILURE);
  } else if (pid < 0) {
    status = -1;
  } else {
    if(waitpid(pid, &status, 0) != pid)
      status = -1;
  }

  free(args_command);
  i = i - 1;
  while(i > -1)
    free(paramList[i--]);

  return status;
}

/**
 * Copies from source string to destination string from a specified range.
 *
 * @param dest Destination string to be copied to.
 * @param src Source string to be copied from.
 * @param begin Starting index to copied from.
 * @param end End index to be copied from.
 * @return
 */
void strcpy_range(char** dest, char** src, int begin, int end) {
  if((*dest) == NULL)
    perror("Failed to allocate memory.\n");

  /* Copy from src[begin] until src[end] to dest */
  int i = 0;
  for(i=0;i<strlen(*src);i++) {
    if(begin == end)
      break;
    (*dest)[i] = (*src)[begin++];
  }
}

/**
 * Change environment variable value.
 *
 * @param env Stores environment variables' values.
 * @param env_var Environment variable to be modified.
 * @param env_val Environment variable to be changed to.
 * @return
 */
void change_env_var(EnvVariable** env, char** env_var, char** env_val) {
  //printf("Current HOME: %s\n", (*env)->home);
  //printf("Current PATH: %s\n", (*env)->path);
  if(strcmp((*env_var),"$HOME=") == 0) {
    free((*env)->home);
    (*env)->home = (char*)malloc(sizeof(char)*strlen(*env_val));
    strcpy((*env)->home, (*env_val));
  } else if (strcmp((*env_var), "$PATH=") == 0) {
    free((*env)->path);
    (*env)->path = (char*)malloc(sizeof(char)*strlen(*env_val));
    strcpy((*env)->path, (*env_val));
  } else {
    fprintf(stderr, "Environment variable does not exist.");
  }
  //printf("Current HOME: %s\n", (*env)->home);
  //printf("Current PATH: %s\n", (*env)->path);
}

/**
 * Search for binary executable in profile's Path.
 *
 * @param bin Binary name to search for.
 * @param env Stores profile environment variables' value.
 * @result Returns -1 for no result and 0 for result.
 */
int search_bin(char** bin, EnvVariable** env, char** result) {
  /* Tokenize */
  char* path = (char*)malloc(sizeof(char)*strlen((*env)->path));
  strcpy(path,(*env)->path);

  char* token = strtok(path, ":");
  while(token != NULL) {
    //printf("PATH: %s\n", token);
    /* Open directory and find for binary executable */
    DIR* dp;
    struct dirent* entry;
    if((dp = opendir(token)) == NULL) {
      fprintf(stderr,"cannot open directory: %s\n", token);
    } else {
      //printf("Directory %s\n", token);
      while((entry = readdir(dp)) != NULL) {
        //int total_len = strlen(token) + strlen(entry->d_name) + 1;
        if(strcmp(entry->d_name, *bin) == 0) {
          //printf("Path of binary: %s/%s\n", token, entry->d_name);

          /* allocate memory */
          *result = (char*)malloc(sizeof(char)*(strlen(token) + strlen(entry->d_name))+2);
          strcpy((*result), token);
          strcat((*result), "/");
          strcat((*result), entry->d_name);

          closedir(dp);
          free(path);
          return 0;
        } else {
          //printf("%s ?= %s -> %i\n", *bin, entry->d_name, strlen(entry->d_name));
        }
      }
    }
    token = strtok(NULL,":");
  }

  printf("Current path: %s\n", (*env)->path);
  free(path);
  return -1;
}

/**
 * Get current directory.
 *
 * @param dir Stores current directory.
 * @return
 */
void get_current_dir(char** dir) {
  char tmp[1024];
  if(getcwd(tmp, sizeof(tmp)) != NULL)
    strcpy((*dir), tmp);
  else {
    (*dir) = NULL;
    perror("getcwd() error.");
  }
}

/**
 * Read environment variables' values.
 *
 * @param profile Profile file to read from.
 * @return
 */
void read_env_val(const char* profile, EnvVariable** env) {
  FILE *infile;
  char line_buffer[BUFSIZ]; /* BUFSIZ is defined if you include stdio.h */
  infile = fopen(profile, "r");
  if (!infile) {
    printf("Couldn't open file %s for reading.\n", profile);
  }

  while (fgets(line_buffer, sizeof(line_buffer), infile)) {
    if(strstr(line_buffer,"HOME") != NULL) {
      char* tmp;
      remove_str(line_buffer, "HOME=", &tmp);
      (*env)->home = tmp;
      //printf("%s",tmp);
    }
    else if(strstr(line_buffer,"PATH") != NULL) {
      char* tmp;
      remove_str(line_buffer, "PATH=", &tmp);
      (*env)->path = tmp;
      //printf("%s",tmp);
    }
  }
}

/**
 * Remove substring from string.
 *
 * @param buffer Source string.
 * @param string String to be removed from source string.
 * @param result Stores modified source string.
 * @result
 */
void remove_str(char* buffer, char* string, char **result) {
  int len_buffer = 0;
  int len_string = 0;
  while(buffer[len_buffer] != '\0') {
    ++len_buffer;
  }
  while(string[len_string] != '\0') {
    ++len_string;
  }
  int index = 0;
  int i = 0;
  char *tmp = malloc(sizeof(char)*(len_buffer - len_string));
  for(i=len_string;i<len_buffer;i++) {
    tmp[index] = buffer[i];
    index++;
  }
  *result = tmp;
}
