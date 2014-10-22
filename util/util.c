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
  int i = 1;

  /* Actual loop */
  while(1) {
    printf("Loop %i\n", i);
    current_dir(&dir);
    printf("%s>", dir);
    fgets(cmd, MAX_SIZE, stdin);
    printf("Command: %s\n", cmd);
    printf("Length of command: %i\n", strlen(cmd));

    /* Reset memory */
    memset(dir, '\0', sizeof(dir));
    memset(cmd, '\0', sizeof(cmd));
    i++;
  }




  int flag = chdir("..");
  if (flag == 0) {
    current_dir(&dir);
    printf("Change to directory: %s\n", dir);
  } else if(flag == -1) {
    printf("Couldnt change directory.");
    current_dir(&dir);
    printf("Current directory: %s\n", dir);
  } else {
    perror("Unexpected error.");
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
  } else if (strcmp(dir, "..")) {
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
    memset((*dir), 0, sizeof((*dir)));
    perror("getcwd() error");
  }
}

void command_parser(char* input, EnvVariable** env) {
  /* Parse command */
  if (input != NULL) {
    /* Check for in-built commands */
    if (strcmp(input,"cd") == 0) {

    } else if(strcmp(input,"pwd") == 0) {

    } else {
      /* Checking for attempt to execute executable */
      /* Executing none in-built commands */
      char *command = input;
      /* Split command from arguments */
    }
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
