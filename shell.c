#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

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

	copy = strdup(lineptr);
	if (copy == NULL)
		exit(-1);

	token = strtok(copy, " ");
	word_count = 0;
	while (token != NULL)
	{
		word_count++;
		token = strtok(NULL, " ");
	}
	word_count++;
	free(copy);

	return (word_count);
}

/**
 * tokenize_input - splits the string by using the space between words
 * as delimeter. Hence, converting the string into an array of words
 *
 * @lineptr: The string to be split
 * @word_count: The number of words in lineptr
 *
 * Return: an array of each word in lineptr
 */
char **tokenize_input(char *lineptr, int word_count)
{
	char *token, **command;
	int i, j;


	command = malloc(sizeof(char *) * word_count);
	if (command == NULL)
		exit(-1);

	token = strtok(lineptr, " ");
	i = 0;
	while (token != NULL)
	{
		command[i] = strdup(token);
		if (command[i] == NULL)
		{
			for (j = 0; j < i; j++)
				free(command[j]);
			free(command);
			exit(-1);
		}
		token = strtok(NULL, " ");
		i++;
	}
	command[i] = NULL;

	return (command);
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

	while (1)
	{
		char **command, *lineptr = NULL;
		int j, status, word_count;
		size_t n = 0;
		ssize_t chars_read;
		pid_t child_pid;

		if (interactive)
			printf("$ ");
		chars_read = getline(&lineptr, &n, stdin);
		if (chars_read == -1)
			exit(-1);

		word_count = count_words(lineptr, chars_read);
		command = tokenize_input(lineptr, word_count);
		free(lineptr);

		if (word_count <= 1)
			continue;
		child_pid = fork();
		if (child_pid == -1)
			exit(-1);
		if (child_pid == 0)
		{
			if (execve(command[0], command, envp) == -1)
			{
				perror("execve");
				_exit(1);
			}
		}
		else
		{
			wait(&status);
			for (j = 0; j < word_count; j++)
				free(command[j]);
			free(command);
		}
		if (!interactive && word_count <= 1)
			break;
	}
	return (0);
}
