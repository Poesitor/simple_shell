#include "shell.h"

/**
 * start_process - Forks and executes a command in a child process.
 *
 * @command: The command to execute
 * @environ: The environment variables.
 * @prog_name: The name of the calling program
 *
 * Return: void
 */
void start_process(char *path, char *args[], char **environ, char *prog_name)
{
	int status;
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Fork error:");
		_exit(1);
	}
	else if (child_pid == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			perror(prog_name);
			_exit(1);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - Reads and executes commands from user or input streams.
 *
 * @ac: argument count
 * @argv: argument vector
 * @environ: environment variables
 *
 * Return: 0 (success), 1 (failure).
 */
int main(__attribute__((unused)) int ac, char **argv, char **environ)
{
	char *buffer, *copy, *token, *path;
	char *cmdargs[4];
	int chars_read, i;
	size_t n = 0;
	int interactive = isatty(STDIN_FILENO);

	buffer = NULL;
	if ((chars_read = _getline(&buffer, &n, stdin)) == -1)
	{
		perror("error");
		return (1);
	}

	while (1)
	{
		if (interactive)
			printf("($) ");

		if (chars_read > 0 && buffer != NULL)
		{
			if (buffer[chars_read - 1] == '\n')
				buffer[chars_read - 1] = '\0';

			i = 0;
			copy = _strdup(buffer);
			free(buffer);
			path = _strtok(copy, " ");
			cmdargs[i++] = path;
			while ((token = _strtok(NULL, " ")) != NULL)
			{
				if (_strcmp(token, "") == 0)
					continue;
				cmdargs[i++] = token;
			}
			cmdargs[i] = token;
			if (_strcmp(path, "") != 0)
			{
				start_process(path, cmdargs, environ, argv[0]);
				free(copy);
			}
			buffer = NULL;
		}

		chars_read = _getline(&buffer, &n, stdin);
		if (!interactive && chars_read <= 0)
			break;
	}

	if (chars_read == -1)
	{
		perror("error");
		return (1);
	}
	return (0);
}
