#include "util.h"

void read_env_val(const char* profile, Terminal** terminal) {
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
      ((*terminal)->env)->home = tmp;
      //printf("%s",tmp);
    }
    else if(strstr(line_buffer,"PATH") != NULL) {
      char* tmp;
      replace(line_buffer, "PATH=", &tmp);
      ((*terminal)->env)->path = tmp;
      //printf("%s",tmp);
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
