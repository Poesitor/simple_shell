#include "main.h"

/**
 * _puts - prints a string followed by a new line
 *
 * @s: The pointer to the string
 *
 * Return: void
 */
void _puts(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		_putchar(s[i]);
}
