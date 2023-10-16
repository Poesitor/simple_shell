#include "main.h"

/**
 * _strlen - returns the length of a string
 *
 * @s: The pointer to the string
 *
 * Return: The length of s
 */
int _strlen(const char *s)
{
	int len, i;

	len = 0;
	for (i = 0; s[i] != '\0'; i++)
		len++;

	return (len);
}
