#ifndef HEADER_H
#define HEADER_H

#define BUFFSIZE 7000

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

/*String*/
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *str1, const char *str2, int n);
int _atoi(char *s);
int _strlen(char *s);

/*Free*/
void liberar_pathname(char *pathname);
void liberar_arg_aux(char ***arg_aux, int pos);
int safty_nets(char *checking, char *str5, ...);
void liberar_paths(va_list list);
void liberar_nodo(list_t *a_liberar);
void liberar_argv(va_list list);
void liberar_index(va_list list);
void liberar_buffer(va_list list);

/*Builtins*/
int check_builtins(int pos1, int flag, char ***arg_aux);
void salir(char **argv);
void env(char **argv);
void cd(char **argv);

/*Paths*/
int check_paths(char **argv);
list_t *create_paths();

/*Aux*/
int largo(int *index);
void _puts(char *str);
int _putchar(char c);

/*Input*/
char *take_input();
int *space_remover(char *to_remove);
char ***separator(char **argv);
char **ar(char *buffer, int *index);

/*Enviroment*/
char *_getenv(const char *name);
void print_env();
void update_old_pwd();
void update_pwd();

#endif
