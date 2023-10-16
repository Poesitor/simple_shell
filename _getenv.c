#include "main.h"

/**
 * _getenv - gets an environment variable from the environment list
 *
 * @name: the name of the variable to get
 *
 * Return: a pointer to the corresponding value string
 */
char *_getenv(const char *name)
{
	int i = 0;
	char *token, *element, *value;

	if (name == NULL)
		return (NULL);

	while (environ[i] != NULL)
	{
		element = _strdup(environ[i]);
		if (element == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}

		token = _strtok(element, "=");
		if (token == NULL)
		{
			free(element);
			i++;
			continue;
		}

		if (_strcmp(token, name) == 0)
		{
			free(element);
			value = environ[i] + (_strlen(name) + 1);
			if (value == NULL)
				return (NULL);
			return (value);
		}
		free(element);
		i++;
	}
	return (NULL);
}
