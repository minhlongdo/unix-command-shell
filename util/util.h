#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../datastructure/terminal.h"

/* Find environment variable */
void read_env_val(const char* profile, Terminal** terminal);
/* Replace string */
void replace(char* buffer, char* string, char** result);

#endif
