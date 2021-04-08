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

typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;


typedef struct datatype
{
	char type;
	int (*func)(va_list list);
} data_t;


#endif
