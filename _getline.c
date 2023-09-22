#include "shell.h"

/**
 * _getline - reads an entire line from stream,
 * storing the address of the buffer containing the text into *lineptr.
 * The buffer is null-terminated and includes
 * the newline character, if one was found.
 *
 * @stream: The input stream to read from
 * @lineptr: a pointer to the buffer containing the text
 * @n: the size in bytes of the buffer
 *
 * Return: On success, _getline() returns the number of characters read,
 * not including the null byte ('\0').
 * On failure to read a line, -1 is returned.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int i, ch;
	char *buffer;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (-1);

	i = 0;
	while ((ch = fgetc(stream)) != EOF)
	{
		if (i >= BUFFER_SIZE - 1)
		{
			buffer = realloc(buffer, BUFFER_SIZE * 2 + 1);
			if (buffer == NULL)
			{
				free(buffer);
				return (-1);
			}
		}

		buffer[i] = ch;
		i++;
		if (ch == '\n')
			break;
	}
	buffer[i] = '\0';
	*n = i + 1;
	free(*lineptr);

	*lineptr = buffer;

	return (i);
}
