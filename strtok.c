#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "shell.h"

/**
 * _strtok - func tokens string based on a DElimiter
 *
 * @str: the string to operate
 * @delim: the delimiter
 *
 * Return: the pointer to string
 * or NULL if no match
 *
 */
char *_strtok(char *str, const char *delim)
{
	const char *org = delim;
	int equal = 1, GTinto = 0;
	static char *stp, *stpNull;
	static int isend;

	if (str)
		isend = 0;
	if (isend)
		return (NULL);
	stp = (str) ? str : (stpNull + 1);
	if (str)
		stpNull = str;
	else
		str = stp;
	while (*str && equal)
	{
		equal = 0;
		for (delim = org; *delim; delim++)
			if (*str == *delim)
				equal = 1;
		str = (!equal) ? str : str + 1;
		isend = (*str) ? 0 : 1;
		if (isend)
			return (NULL);
	}
	stp = str;
	while (*str && !equal)
	{
		equal = 0;
		for (delim = org; *delim; delim++)
			if (*str == *delim)
			{
				GTinto = 1, equal = 1;
				isend = (*(str + 1)) ? 0 : 1, *str = '\0';
			}
		str = (equal) ? str : str + 1;
		if (!GTinto && !*str)
			isend = 1;
	}
	return (stpNull = str, stp);
}
