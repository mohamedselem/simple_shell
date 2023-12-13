#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "shell.h"

/**
 * checkInput - func do check for input in after shell prompt
 * @ac: the count of main argus
 * @av: the main argus
 * @bufsize: the size of buffers in prompt
 * @buffer: the buffers in prompt
 * @shpack: the struct of shell information
 *
 * Return: On success 1.
 * On error, -1 is returned, and err is set appropriately.
 */
char **checkInput(int ac, char **av, size_t *bufsize,
		   char **buffer, hshpack *shpack)
{
	ssize_t charac;
	char **comm;
	int extnm;

	if (ac == 1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		charac = getline(buffer, bufsize, stdin);

		if (charac == -1)
		{
			extnm = shpack->extnm[0];
			free(*buffer);
			if (*(shpack->envCpy))
				free_doubpoint(*(shpack->envCpy));
			free(shpack);
			if (isatty(STDIN_FILENO))
				write(1, "\n", 1);
			exit(extnm);
		}
		if (**buffer == '#' || !charac || **buffer == '\n')
			return (NULL);
		*buffer = deleteComment(*buffer);
		comm = getParameters(*buffer, shpack);
	}
	else
	{
		comm = malloc(sizeof(char *) * (ac - 1));
		if (!comm)
		{
			_error(7, shpack, 1);
			return (NULL);
		}

		comm[ac - 1] = '\0';
		while (ac--)
			comm[ac - 1] = av[ac];
	}
	return (comm);
}

/**
 * deleteComment - func do deletes commnet inside command line
 *
 * @str: the string to be operated
 *
 * Return: the pointer to string
 *
 */
char *deleteComment(char *str)
{
	char *organ = str;

	for (; str && *str; str++)
		if (*str == '#' && *(str - 1) == ' ')
		{
			*str = '\0';
			break;
		}

	return (organ);
}
