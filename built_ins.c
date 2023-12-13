#include <limits.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "shell.h"

/**
 * _exit_cmd - func of built in command exit
 * @shpack: the struct containing shell info
 *
 * Return: -1 if error
 */
ssize_t _exit_cmd(hshpack *shpack)
{
	long valToExit;

	if (shpack->options[1] == NULL || _isnumber(shpack->options[1]))
	{
		valToExit = _atoi(shpack->options[1]);

		if (valToExit >= 0 && valToExit < INT_MAX)
		{
			if (valToExit > 255)
				valToExit %= 256;
			if (shpack->options[1] == NULL)
				valToExit = shpack->exitnum[0];
			free(*(shpack->options));
			free(shpack->options);
			if (*(shpack->envCpy))
				free_doubpoint(*(shpack->envCpy));
			free(shpack);
			exit(valToExit);
		}
	}

	_error(2, shpack, 2);
	free(shpack->options);
	return (-1);
}
/**
 * _env_cmd - function of built in command env
 * @shpack: the struct containing shell info
 *
 * Return: 1 if succesful
 */
ssize_t _env_cmd(hshpack *shpack)
{
	char **str1;
	int check1 = 1;

	if (*(shpack->envCpy) == NULL)
	{
		write(2, "ENVIROMENT is Null, Can not Print it\n", 36);
		shpack->exitnum[0] = 2;
		free(shpack->options);
		return (-1);
	}

	str1 = *(shpack->envCpy);

	if (shpack->options[1] == NULL)
	{
		for (; str1 && *str1; str1++)
		{
			write(1, *str1, _strlen(*str1));
			write(1, "\n", 1);
		}
	}
	else
	{
		_error(0, shpack, 2);
		check1 = -1;
	}

	free(shpack->options);
	return (check1);
}
/**
 * _setenv_cmd - functin built in command setenv
 * @shpack: the struct contain shell info
 *
 * Return: 1 if succesful, -1 if fail
 */
ssize_t _setenv_cmd(hshpack *shpack)
{
	char **newenv1;
	char *variable2 = NULL;
	char *value3 = NULL;

	if (shpack->options[1])
	{
		variable2 = shpack->options[1];
		if (!shpack->options[2])
		{
			write(2, "Invalid VALUE\n", 14);
			shpack->exitnum[0] = 2;
			free(shpack->options);
			return (-1);
		}
		else
			value3 = shpack->options[2];

	}
	if (variable2 == 0)
	{
		write(2, "Invalid VARIABLE\n", 17);
		shpack->exitnum[0] = 2;
		free(shpack->options);
		return (-1);
	}

	newenv1 = _setenv(*(shpack->envCpy), variable2, value3, shpack);

	if (newenv1 == 0)
	{
		free(shpack->options);
		return (-1);
	}

	*(shpack->envCpy) = newenv1;
	free(shpack->options);
	return (1);
}
/**
 * _unsetenv_cmd - func built in command Unsetenv
 * @shpack: the struct containing shell info
 *
 * Return: 1 if succesful, -1 if fail
 */
ssize_t _unsetenv_cmd(hshpack *shpack)
{
	char **newenv1;
	char *variable2 = NULL;

	if (shpack->options[1])
		variable2 = shpack->options[1];
	else
	{
		shpack->exitnum[0] = 2;
		write(2, "Please provide an argument\n", 27);
		return (free(shpack->options), -1);
	}

	if (variable2 == 0)
	{
		free(shpack->options);
		return (1);
	}

	newenv1 = _unsetenv(*(shpack->envCpy), variable2, shpack);

	if (newenv1 == 0 && shpack->unsetnull[0] == 0)
	{
		free(shpack->options);
		shpack->exitnum[0] = 2;
		return (-1);
	}

	*(shpack->envCpy) = newenv1;
	free(shpack->options);
	return (1);
}

/**
 * built_ints - func to checks if CMD is a built in
 * @shpack: the struct containing shell info
 *
 * Return: On fail give 0
 */
ssize_t built_ints(hshpack *shpack)
{
	b_ins ops[] = {
		{"exit", _exit_cmd},
		{"env", _env_cmd},
		{"setenv", _setenv_cmd},
		{"unsetenv", _unsetenv_cmd},
		{"cd", _cd_cmd},
		{"help", _help_cmd}
	};

	int q = 6, builtcheck;

	while (q--)
		if (!_strcmp(shpack->cmd, ops[q].cmd))
		{
			shpack->errnum[0] += 1;
			builtcheck = ops[q].f(shpack);
			if (builtcheck == 1)
				shpack->exitnum[0] = 0;
			return (builtcheck);
		}

	return (0);
}
