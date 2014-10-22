#include "init.h"

/**
 * Initialize necessary data for unix command shell.
 *
 * @param env Stores environment variables value from file profile.
 * @return
 */
void init(EnvVariable** env) {
  read_env_val("profile", &(*env));
}
