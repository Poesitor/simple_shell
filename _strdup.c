#include "main.h"

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter
 *
 * @str: The string to be copied
 *
 * Return: (On success) a pointer to the newly allocated space in memory,
 * (On failure) returns NULL.
 */
char *_strdup(char *str)
{
	char *copy;
	int i;
	int strlen = 0;

	if (str == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		strlen += 1;

	copy = malloc(sizeof(char) * (strlen + 1));
	if (copy == NULL)
		return (NULL);

	else
	{
		for (i = 0; i <= strlen; i++)
			copy[i] = str[i];
	}

	return (copy);
}
