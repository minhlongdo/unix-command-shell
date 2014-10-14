#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../datastructure/env.h"

void read_env_val(const char* profile, EnvVariable** env); 					 /* Find environment variable */
void replace(char* buffer, char* string, char** result); 						 /* Replace string */

#endif
