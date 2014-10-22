#include "init.h"

void init(EnvVariable** env) {
  read_env_val("profile", &(*env));
}
