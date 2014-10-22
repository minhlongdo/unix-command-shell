#include "util.h"

void terminal_main(EnvVariable** env) {
  char* cmd = (char*)malloc(sizeof(char)*MAX_SIZE);
  char* dir = (char*)malloc(sizeof(char)*1024);

  current_dir(&dir);

  printf("Current directory: %s\n", dir);

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

  /* Reset memory */
  memset(dir, '\0', sizeof(dir));

  /* Release memory */
  free(cmd);
  free(dir);
}

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
