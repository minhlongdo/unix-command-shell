#include "builtin.h"

/**
* Change directory.
*
* @param dir Directory to change to.
* @return
*/
void change_dir(char** dir, EnvVariable** env) {
	char* debug = (char*)malloc(sizeof(char)*1024);
	get_current_dir(&debug);
	printf("Current dir: %s\n", debug);

	int flag = -1;
	if((*dir) == NULL) {
		flag = chdir((*env)->home);
		if (flag == -1) {
			fprintf(stderr, "directory %s does not exist.\n", (*env)->home);
		} else {
			memset(debug, '\0', 1024);
			printf("Directory change successful.\n");
			get_current_dir(&debug);
			printf("Changed dir: %s\n", debug);
		}
	} else {
		flag = chdir((*dir));
		if (flag == -1) {
			fprintf(stderr, "directory %s does not exist.\n", (*dir));
		} else {
			memset(debug, '\0', 1024);
			printf("Directory change successful.\n");
			get_current_dir(&debug);
			printf("Changed dir: %s\n", debug);
		}
	}
	free(debug);
}
