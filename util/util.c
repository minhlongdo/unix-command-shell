#include "util.h"

void read_env_val(const char* profile) {
  FILE *infile;
  char line_buffer[BUFSIZ]; /* BUFSIZ is defined if you include stdio.h */
  char line_number;
  infile = fopen(profile, "r");
  if (!infile) {
    printf("Couldn't open file %s for reading.\n", profile);
  }

  while (fgets(line_buffer, sizeof(line_buffer), infile)) {
    if(strstr(line_buffer,"HOME") != NULL) {
    }
    else if(strstr(line_buffer,"PATH") != NULL) {
    }
  }
}
