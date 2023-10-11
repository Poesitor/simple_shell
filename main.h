#ifndef MAIN_H
#define MAIN_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>

extern char **environ;

/**
 * struct path_s - a linked list of path directories
 *
 * @path: The path to a command
 * @next: points to the next path
 *
 * Description: singly linked list of path directories
 */
typedef struct path_s
{
	char *path;
	struct path_s *next;
} path_t;

char *_strtok(char *str, const char *delim);
char *append(const char *str1, const char *str2);
int _strcmp(const char *s1, const char *s2);
char *_getenv(const char *name);
char *join_ch(const char *str1, const char *str2, const char ch);
int _setenv(const char *name, const char *value, int overwrite);

#endif /* MAIN_H */