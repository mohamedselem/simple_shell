#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "shell.h"
/**
 * getParameters - func do obtains parameters from buffer of prompt
 * @raw_buffer: raw_buffer
 * @shpack: the struct containing shell info
 *
 * Return: On success 1.
 * On error, -1 is returned, and error is set appropriately.
 */
char **getParameters(char *raw_buffer, hshpack *shpack)
{
	char **buffer, *cp_raw_buffer;
	ssize_t c = 0, n = 0;

	cp_raw_buffer = _strdup(raw_buffer);
	if (!cp_raw_buffer)
	{
		_error(7, shpack, 1);
		exit(-1);
	}

	if (_strtok(cp_raw_buffer, " \n"))
		c++;
	else
	{
		free(cp_raw_buffer);
		return (NULL);
	}
	while (_strtok(NULL, " \n"))
		c++;

	free(cp_raw_buffer);
	buffer = malloc(sizeof(char *) * (c + 1));
	if (!buffer)
	{
		_error(7, shpack, 1);
		exit(-1);
	}
	buffer[0] = _strtok(raw_buffer, " \n");
	for (n = 1; n < c && buffer[n - 1]; n++)
		buffer[n] = _strtok(NULL, " \n");

	if (!buffer[n - 1])
	{
		free_doubpoint(buffer);
		return (NULL);
	}

	buffer[n] = NULL;
	return (buffer);
}
