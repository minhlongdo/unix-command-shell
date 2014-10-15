#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../datastructure/terminal.h"

void read_env_val(const char* profile, Terminal** terminal); 				 /* Find environment variable */
void replace(char* buffer, char* string, char** result); 						 /* Replace string */
void command_parser(char* input, Terminal** terminal);               /* Parse command */

#endif
