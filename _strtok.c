#include "main.h"

/**
 * _strtok - extracts tokens from strings (like strtok)
 *
 * @str: The string to be split
 * @delim: The set of bytes that delimits the tokens in the spring.
 *
 * Return: A pointer to the next token in the string,
 * excluding the delimiting byte.
 * returns NULL is no more tokens are found
 */
char *_strtok(char *str, const char *delim)
{
	static char *next_token;
	static int called = -1;
	int i = 0, j = 0;

	if (str != NULL)
		called = 1;

	if (str == NULL)
	{
		if (called < 1)
			return (NULL);
		else if (next_token == NULL)
			return (NULL);
		str = next_token;
	}

	if (str[i] == '\0')
		return (NULL);
	while (str[i] == *delim)
	{
		i++;
		if (str[i] == '\0')
			return (NULL);
	}
	j = i;
	for (; str[i] != '\0'; i++)
	{
		if (str[i] == *delim)
		{
			str[i] = '\0';
			next_token = &str[i + 1];
			return (&str[j]);
		}
	}

	next_token = NULL;
	return (&str[j]);
}
