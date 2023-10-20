#include "main.h"

/**
 * no_path - prints error message and exits the executing process
 *
 * @name: program name
 * @num: the line number the command was found
 * @cmd: The command intended to be run
 * @ex_code: a pointer to the exit code of the main function
 *
 * Return: void
 */
void no_path(char *name, int num, char **cmd, int *ex_code)
{
	int count = 0;
	int temp = num;
	char *num_str;
	char *command = cmd[0];
	char *err_msg = "not found\n";

	while (temp != 0)
	{
		temp /= 10;
		count++;
	}

	num_str = malloc(sizeof(char) * (count + 1));
	if (num_str == NULL)
	{
		perror("malloc fail");
		_exit(EXIT_FAILURE);
	}
	num_str[count] = '\0';
	while (count > 0)
	{
		count--;
		num_str[count] = num % 10 + '0';
		num /= 10;
	}

	write(STDERR_FILENO, name, _strlen(name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, num_str, _strlen(num_str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, err_msg, _strlen(err_msg));

	free(num_str);

	*ex_code = 127;
}

/**
 * count_words - count the number of words in a string
 *
 * @lineptr: the string
 * @chars_read: the number of characters in the string,
 * including new line if found
 * Return: the number of words in lineptr
 */
int count_words(char *lineptr, ssize_t chars_read)
{
	int word_count;
	char *token, *copy;

	if (lineptr[chars_read - 1] == '\n')
		lineptr[chars_read - 1] = '\0';

	copy = _strdup(lineptr);
	if (copy == NULL)
	{
		perror("strdup fail");
		exit(EXIT_FAILURE);
	}

	token = _strtok(copy, " ");
	word_count = 0;
	while (token != NULL)
	{
		word_count++;
		token = _strtok(NULL, " ");
	}
	word_count++;
	free(copy);

	return (word_count);
}

/**
 * sighandler - handles the signal interrupt
 * @sig: unused variable necessary for sighandler function types
 */
void sighandler(int sig)
{
	(void)sig;
	_puts("\n($) ");

	signal(SIGINT, sighandler);
}
/**
 * execute - checks if a command exists and executes it
 *
 * @cmd: a list of strings that represents the command to be executed
 * @prog: The name of the compiled program file
 * @line: The line of input command into the current process
 * @env: a list of environment variables
 * @ex_code: a pointer to the exit code of the proram
 * Return: void
 */

void execute(char **cmd, char *prog, int line, char **env, int *ex_code)
{
	char *path;
	int status, j;
	pid_t child_pid = 1;

	if (access(cmd[0], X_OK) == 0)
		path = _strdup(cmd[0]);
	else
		path = which(cmd[0]);
	if (path == NULL || access(path, X_OK) != 0)
		no_path(prog, line, cmd, ex_code);
	else
		child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (execve(path, cmd, env) == -1)
			perror("execve");
		*ex_code = EXIT_FAILURE;
		for (j = 0; cmd[j] != NULL; j++)
			free(cmd[j]);
		free(cmd);
	}
	else
	{
		wait(&status);
		free(path);
		if (cmd != NULL)
		{
			for (j = 0; cmd[j] != NULL; j++)
				free(cmd[j]);
			free(cmd);
		}
	}
}

/**
 * main - runs commands with their full path without any argument
 *
 * @argc: argument count
 * @argv: argument vector
 * @envp: current environment variables
 *
 * Return: Always 0.
 */
int main(int argc, char *argv[], char *envp[])
{
	int interactive = isatty(STDIN_FILENO);
	int line_num = 0;
	int ex_code = 0;

	(void) argc;
	signal(SIGINT, sighandler);

	while (1)
	{
		char **command, *lineptr = NULL;
		int word_count;
		size_t n = 0;
		ssize_t chars_read;

		if (interactive)
			_puts("($) ");
		chars_read = getline(&lineptr, &n, stdin);
		line_num++;
		if (chars_read == -1)
		{
			if (interactive)
				_putchar('\n');
			free(lineptr);
			break;
		}

		word_count = count_words(lineptr, chars_read);
		command = tokenize_input(lineptr, word_count);
		free(lineptr);
		if (check_builtins(command, ex_code) == -1)
			continue;

		if (word_count <= 1)
			continue;
		execute(command, argv[0], line_num, envp, &ex_code);
	}
	exit(ex_code);
}
