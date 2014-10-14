#ifndef _TERMINAL_H
#define _TERMINAL_H

#include "env.h"

typedef struct Terminal {
  EnvVariable *env;
  char* cur_dir;
} Terminal;

#endif
