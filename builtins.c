#include "main.h"

/**
 * shell_exit - function to exit the shell
 *
 * @command: a pointer to an array of commands given by the user
 * @ex_code: a pointer to the exit code of the main program
 *
 * Return: 0 on success, -1 if user exit code is invalid
 */
int shell_exit(char **command, int ex_code)
{
	int i;

	if (command[1] == NULL)
	{
		for (i = 0; command[i] != NULL; i++)
			free(command[i]);
		free(command);
		exit(ex_code);
	}
	else
	{
		ex_code = _atoi(command[1]);
		if (ex_code == -1)
		{
			_puts("Illegal number\n");
			return (-1);
		}
		for (i = 0; command[i] != NULL; i++)
			free(command[i]);
		free(command);


		exit(ex_code);
	}
	return (ex_code);
}
