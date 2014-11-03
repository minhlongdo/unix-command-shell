#include "init.h"

/**
 * Initialization process upon startup of unix shell.
 *
 * @param env Stores PATH and HOME values.
 * @return
 */
void init(EnvVariable** env) {
  read_env_val("profile", &(*env));
}
