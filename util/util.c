#include "util.h"

/**
 * Main body of unix command shell.
 *
 * @param env Contains environment variables' values.
 * @return
 */
void terminal_main(EnvVariable** env) {
  char* cmd = (char*)malloc(sizeof(char)*MAX_SIZE);
  char* dir = (char*)malloc(sizeof(char)*1024);

  /* Actual loop */
  while(1) {
    current_dir(&dir);
    printf("%s>", dir);
    fgets(cmd, MAX_SIZE, stdin);

    /* Parse command and trigger appropriate handler */
    command_parser(&cmd, &(*env));

    /* Reset memory */
    memset(dir, '\0', sizeof(dir));
    memset(cmd, '\0', sizeof(cmd));
  }

  /* Release memory */
  free(cmd);
  free(dir);
}

/**
 * Change directory based on the given path (unix convention).
 *
 * @param dir Directory to change to.
 * @param env Contains environment variables value from file profile.
 * @return
 */
void change_dir(char* dir, EnvVariable** env) {
  char* dir_debug = (char*)malloc(sizeof(char)*1024);
  int flag = -1;
  if (dir == NULL) {
    /* Change to assigned home directory written in the profile */
    flag = chdir((*env)->home);
    if (flag == -1) {
      perror(("Directory '%s' does not exist.\n", (*env)->home));
    } else {
      printf("Directory change successful.\n");
      current_dir(&dir_debug);
      printf("Current directory: %s\n", dir_debug);
    }
  } else if (strcmp(dir, "..") == 0) {
    flag = chdir(dir);
    if (flag == -1) {
      current_dir(&dir_debug);
      perror(("Directory parent '%s' does not exist.\n", dir_debug));

    } else {
      printf("Directory change to parent directory successful.\n");
      current_dir(&dir_debug);
      printf("Current directory: %s\n", dir_debug);
    }
  }
  free(dir_debug);
}

/**
 * Get the current directory.
 *
 * @param dir Stores current directory.
 * @return
 */
void current_dir(char** dir) {
  char tmp[1024];
  if(getcwd(tmp,sizeof(tmp)) != NULL) {
    /* Copy array to pointer */
    strcpy((*dir), tmp);
  }
  else {
    /* Reset string */
    memset((*dir), 0, sizeof(&(*dir)));
    perror("getcwd() error");
  }
}

/**
 * Parse and tokenize command input and trigger appropriate event.
 *
 * @param cmd Command to be parsed.
 * @param env Stores environment variables' values.
 * @return
 */
void command_parser(char** cmd, EnvVariable** env) {
  /* If memory was allocated for it */
  if ((*cmd) == NULL)
    return;

  /* Remove white space at the end of the string */
  int len = strlen(*cmd);
  (*cmd)[len-1] = '\0';

  /* Tokenize command */
  char* token = NULL;
  token = strtok((*cmd), " ");
  char* strArray[40];

  /*
   * Number of tokens.
   * First token is the command.
   * The following tokens are arguments.
   */
  int i = 0;
  if (strstr((*cmd), " ") !=  NULL) {
    while(token != NULL) {
      //printf("[%s]\n", token);
      strArray[i] = (char*)malloc(sizeof(char)*strlen(token));
      strcpy(strArray[i], token);
      //printf("Array string: %s\n",strArray[i]);
      token = strtok(NULL, " ");
      i++;
    }
  } else {
    strArray[i] = (char*)malloc(sizeof(char)*strlen((*cmd)));
    strArray[i] = *cmd;
  }

  char* command = strArray[0];
  //printf("Command: %s\n", command);
  /* Checking for unix in-built commands */
  if (strcmp(command, "cd") == 0) {
    if (i == 2) {
      char* dir_dest = strArray[1];
      printf("Directory destination: %s\n", dir_dest);
      change_dir(dir_dest, &(*env));
    } else if(i < 2) {
      perror("Too few argument.\n");
    } else if (i > 2) {
      perror("Too many arguments.\n");
    }
  } else if (strcmp(command, "ls") == 0) {

  } else if (strcmp(command, "pwd") == 0) {
    char* dir_curr = (char*)malloc(sizeof(char)*1024);
    current_dir(&dir_curr);
    printf("%s\n", dir_curr);
    free(dir_curr);
  } else {
    /* Tokenize environment PATH value */
  }
  /* Free memory */
  while(i > - 1) {
    free(strArray[i]);
    i--;
  }
}

/**
 * Read environment variable values from file.
 *
 * @param profile File to read from.
 * @param env Stores read environment variable values from file.
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
      remove_substring(line_buffer, "HOME=", &tmp);
      (*env)->home = tmp;
    }
    else if(strstr(line_buffer,"PATH") != NULL) {
      char* tmp;
      remove_substring(line_buffer, "PATH=", &tmp);
      (*env)->path = tmp;
    }
  }
}

/**
 * Remove substring in a string with another string.
 *
 * @param buffer Source string.
 * @param string String to be remove in the source string.
 * @param result Stores source string without the removed string.
 * @return
 */
void remove_substring(char* buffer, char* string, char **result) {
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
