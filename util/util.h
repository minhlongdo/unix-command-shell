#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
/* Execute shell command */
int sys_call(char**bin_cmd, char**args);

#endif
