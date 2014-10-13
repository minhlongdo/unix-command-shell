#include "util.h"

void read_env_val(const char* environment_var, const char* profile) {
  FILE *infile;
  char line_buffer[BUFSIZ]; /* BUFSIZ is defined if you include stdio.h */
  char line_number;
  infile = fopen(profile, "r");
  if (!infile) {
    printf("Couldn't open file %s for reading.\n", profile);
  }

  while (fgets(line_buffer, sizeof(line_buffer), infile)) {
    if(strstr(line_buffer,"HOME") != NULL) {
      printf("HOME exists.\n");
    }
    else if(strstr(line_buffer,"PROFILE") != NULL) {
      printf("PROFILE exists.\n");
    }
  }
}
