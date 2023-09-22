#include "string.h"

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
	int i = 0;
	int j = 0;

	if (str == NULL)
		str = next_token;

	if (str == NULL)
		return (NULL);

	while (str[i] == *delim)
		i++;
	j = i;

	while (str[i] != '\0')
	{
		if (str[i] == *delim)
		{
			str[i] = '\0';
			next_token = &str[i + 1];
			return (&str[j]);
		}
		i++;
	}

	next_token = NULL;
	return (&str[j]);
}
