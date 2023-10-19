#include "main.h"

/**
 * check_builtins - checks if a command entered is a builtin
 *
 * @cmd: an array of the commands entered by the user
 *
 */
void check_builtins(char **cmd, int ex_code)
{
	int i = 0;
	built_in_command_t builtins[] = {
		{"exit", shell_exit},
		{NULL, NULL}
	};

	if (cmd[i] == NULL)
		return;

	while (builtins[i].command != NULL)
	{
		if (_strcmp(cmd[0], builtins[i].command) == 0)
		{
			builtins[i].function(cmd, ex_code);
			return;
		}
		i++;
	}
}
