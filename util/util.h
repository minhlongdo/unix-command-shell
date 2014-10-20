#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../datastructure/env.h"

/* Find environment variable */
void read_env_val(const char* profile, EnvVariable** env);
/* Replace string */
void replace(char* buffer, char* string, char** result);
/* Parse command */
void command_parser(char* input, EnvVariable** env);
/* Change directory */
void change_dir(char** curr_dir, char* dir, EnvVariable** env);
/* Get current directory */
char* current_dir(void);
#endif
