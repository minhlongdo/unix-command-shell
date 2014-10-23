#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include "../datastructure/env.h"

/* Find environment variable */
void read_env_val(const char* profile, EnvVariable** env);
/* Replace string */
void remove_str(char* buffer, char* string, char** result);
/* Get current dir */
void get_current_dir(char** dir);
/* Search for executable command */
int search_bin(char** bin, EnvVariable** env, char** result);

#endif
