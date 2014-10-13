#include "init.h"

void* init(void) {
  const char* unix_profile = "profile";
  char* HOME = read_env_val("HOME", unix_profile);
  char* PROFILE = read_env_val("PROFILE", unix_profile);
  EnvVariable* env = malloc(sizeof(EnvVariable));

  while(1) {

  }

  free(env);
}
