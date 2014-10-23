#include "util.h"

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
    printf("PATH: %s\n", token);
    /* Open directory and find for binary executable */
    DIR* dp;
    struct dirent* entry;
    if((dp = opendir(token)) == NULL) {
      fprintf(stderr,"cannot open directory: %s\n", token);
    } else {
      printf("Directory %s\n", token);
      while((entry = readdir(dp)) != NULL) {
        //int total_len = strlen(token) + strlen(entry->d_name) + 1;
        if(strcmp(entry->d_name, *bin) == 0) {
          //printf("Path of binary: %s/%s\n", token, entry->d_name);
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
