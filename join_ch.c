#include "main.h"

/**
 * join_ch - Concatenates two strings with a @ch character in between
 *
 * @str1: First string
 * @str2: Second string
 * @ch: The character between the two strings
 *
 * Return: A pointer to the concatenated string, or NULL on failure
 */
char *join_ch(const char *str1, const char *str2, const char ch)
{
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	char *result = malloc(sizeof(char) * (len1 + len2 + 2));

	if (result == NULL)
	{
		perror("Memory allocation failed");
		return (NULL);
	}

	strcpy(result, str1);
	if (result[len1 - 1] != ch)
	{
		result[len1] = ch;
		len1++;
	}

	strcpy(result + len1, str2);
	return (result);
}
