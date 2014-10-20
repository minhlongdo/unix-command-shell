#include "util.h"

void change_dir(char** curr_dir, char* dir, EnvVariable** env) {
  if (dir != NULL) {
    /* Move up one directory */
    if(strcmp(dir, "..")) {
    } else if(strcmp(dir, "")) {
      /* Change to default directory, specified in the environment variable */
    } else {
      /* Change to specific directory */
      /* Check in current directory */
      /* Check for another absolute directory */
    }
  }
}

char* current_dir(void) {
  char cwd[1024];
  if(getcwd(cwd,sizeof(cwd)) != NULL)
    fprintf(stdout,"%s\n",cwd);
  else
    perror("getcwd() error");
  return cwd;
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
      replace(line_buffer, "HOME=", &tmp);
      (*env)->home = tmp;
    }
    else if(strstr(line_buffer,"PATH") != NULL) {
      char* tmp;
      replace(line_buffer, "PATH=", &tmp);
      (*env)->path = tmp;
    }
  }
}

void replace(char* buffer, char* string, char **result) {
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
