#include "main.h"

/**
 * check_builtins - checks if a command entered is a builtin
 *
 * @cmd: an array of the commands entered by the user
 * @ex_code: a pointer to the exit code of the main program
 *
 * Return: -1 or 0
 */
int check_builtins(char **cmd, int ex_code)
{
	int i = 0;
	built_in_command_t builtins[] = {
		{"exit", shell_exit},
		{"env", printenv},
		{NULL, NULL}
	};

	if (cmd[i] == NULL)
		return (0);

	while (builtins[i].command != NULL)
	{
		if (_strcmp(cmd[0], builtins[i].command) == 0)
		{
			if (builtins[i].function(cmd, ex_code) == -1)
				return (-1);
			return (0);
		}
		i++;
	}
	return (0);
}
