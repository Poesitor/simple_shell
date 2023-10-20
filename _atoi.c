#include "main.h"

/**
 * _atoi - converts a string to integer
 *
 * @string: the string to be converted
 *
 * Return: The int gotten. or -1 if
 * string is not a number
 */
int _atoi(char *string)
{
	int i, num;

	i = 0;
	num = 0;

	while (string[i] != '\0')
	{
		if (string[i] < '0' || string[i] > '9')
			return (-1);
		num *= 10;
		num += string[i] - '0';
		i++;
	}

	return (num);
}
