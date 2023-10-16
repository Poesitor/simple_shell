#include "main.h"

/**
 * _srtcpy - creates the string pointed to by src
 * to the buffer pointed to by dest
 *
 * @src: a pointer to the string to be copied
 * @dest: a pointer to the copy destination
 *
 * Return: void
 */
char *_strcpy(char *dest, const char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return (dest);
}
