#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * _copydoublepDel - func do copy an array of strings
 *
 * @p: the double pointer to be copy
 * @new_size: the size of copy
 * @jump: the value that must SKipped in copy
 *
 * Return: Pointers Malloec
 */
char **_copydoublepDel(char **p, int new_size, int jump)
{
	char **copy;
	int q, z, csize1;

	csize1 = new_size;
	copy = malloc(sizeof(char *) * (csize1 + 1));
	if (copy == 0)
		return (0);

	for (q = 0, z = 0; z < csize1; q++, z++)
	{
		if (q == jump)
			q++;
		copy[z] = _strdup(p[q]);
		if (copy[z] == 0)
		{
			z--;
			for (; z >= 0; z--)
				free(copy[z]);
			free(copy);
			return (0);
		}
	}

	copy[new_size] = '\0';

	return (copy);
}

/**
 * _unsetenv - the unsets of an envir variable
 *
 * @env: the array of envir variables
 * @variable: the envir variable to unset
 * @shpack: the struct with shell information
 *
 * Return: 0 on success, -1 on error
 */
char **_unsetenv(char **env, char *variable, hshpack *shpack)
{
	int q, z, chk, l = 0, len = 0, fund = 0;
	char **copy;

	shpack->unsetnull[0] = 0;
	if (!env)
		return (write(2, "Environment is NULL\n", 20), NULL);
	if (_strlen(variable) == 0 || variable == 0)
		return (_error(3, shpack, 1), NULL);
	l = _strlen(variable), len = _strlendp(env);
	for (q = 0; env[q] != 0; q++)
	{
		for (chk = 0, z = 0; z < l && env[q][z] != 0; z++)
		{
			if (variable[z] == '=')
				return (_error(3, shpack, 2), NULL);
			if (env[q][z] == variable[z])
				chk++;
		}
		if (chk == l && env[q][chk] == '=')
		{

			fund = 1;
			if ((len - 1) != 0)
			{
				copy = _copydoublepDel(env, len - 1, q);
				if (copy == 0)
					return (_error(7, shpack, 1), NULL);
			}
			else
				shpack->unsetnull[0] = 1, copy = NULL;
			free_doubpoint(env), env = copy;
			return (env);
		}
	}
	if (fund == 0)
		return (write(2, "VARIABLE couldn't found\n", 19), NULL);
	return (env);
}
