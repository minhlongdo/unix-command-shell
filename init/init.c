#include "init.h"

void init(Terminal** terminal) {
  read_env_val("profile", &(*terminal));
  (*terminal)->cur_dir = (*terminal)->env->home;
}
