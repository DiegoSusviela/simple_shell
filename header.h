#ifndef HEADER_H
#define HEADER_H

#define BUFFSIZE 1024

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <time.h>
#include <stdarg.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

typedef struct builtins
{
	char *command;
	void (*f)(char **);
} builtins_t;

typedef struct datatype
{
	char type;
	void (*func)(va_list list);
} data_t;

char *_strcat(char *dest, char *src);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *str1, const char *str2, int n);
int _atoi(char *s);
int _strlen(char *s);

void salir(char **argv);
#endif
