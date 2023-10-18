#include "main.h"

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
	{
		perror("malloc fail");
		exit(EXIT_FAILURE);
	}

	token = _strtok(lineptr, " ");
	i = 0;
	while (token != NULL && i < word_count)
	{
		command[i] = _strdup(token);
		if (command[i] == NULL)
		{
			for (j = 0; j < i; j++)
				free(command[j]);
			free(command);
			perror("strdup fail");
			exit(EXIT_FAILURE);
		}
		token = _strtok(NULL, " ");
		i++;
	}
	command[i] = NULL;
	return (command);
}
