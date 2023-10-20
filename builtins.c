#include "main.h"

/**
 * shell_exit - function to exit the shell
 *
 * @command: a pointer to an array of commands given by the user
 * @ex_code: a pointer to the exit code of the main program
 *
 */
void shell_exit(char **command, int ex_code)
{
	int i;

	for (i = 0; command[i] != NULL; i++)
		free(command[i]);
	free(command);

	exit(ex_code);
}