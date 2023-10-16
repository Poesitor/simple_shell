#include "main.h"

/**
 * which - looks for files in the current PATH
 *
 * @file: The file to be found
 *
 * Return: a pointer to the full path of the file (on success),
 * returns NULL (on failure)
 */
char *which(char *file)
{
	char *path, *token, *copy, *fullpath = NULL;
	struct stat st;

	if (file == NULL)
		return (NULL);

	path = _getenv("PATH");
	if (path == NULL)
	{
		perror("PATH environment variable not set");
		return (file);
	}

	copy = _strdup(path);
	if (copy == NULL)
	{
		perror("Memory allocation failed");
		return (NULL);
	}
	token = _strtok(copy, ":");
	while (token != NULL)
	{
		if (file[0] == '/')
			fullpath = _strdup(file);
		else
			fullpath = join_ch(token, file, '/');
		if (stat(fullpath, &st) == 0)
			break;
		free(fullpath);
		token = _strtok(NULL, ":");
		if (token == NULL)
			fullpath = NULL;
	}

	free(copy);
	return (fullpath);
}
