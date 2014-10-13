#include "util.h"

char* read_env_val(char* env_var, char* profile) {
  FILE* fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read = 0;

  fp = fopen(profile, 'r');
  if (fp == NULL)
    fprintf(stderr, "Need to create profile for unix command shell.\n");
    return exit(FAILURE)

  /* Read through every line */
  while((read = getline(&line, &len, fp)) != -1) {
    printf("%s", line);
    if (strstr(line, env_var) != NULL) {
      fclose(fp);
      return line
    }
  }

  printf("Coudln't find specified environment variable in %s\n", profile);
  fclose(fp);
  if (line)
    free(line);
  return NULL;
}
