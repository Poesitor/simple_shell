#include "main.h"

/**
 * shell_exit - function to exit the shell
 *
 * @command: a pointer to an array of commands given by the user
 *
 */
void shell_exit(char **command)
{
	int i;

	for (i = 0; command[i] != NULL; i++)
		free(command[i]);
	free(command);

	exit(0);
}
