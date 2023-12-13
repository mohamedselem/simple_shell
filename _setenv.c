#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * free_doubpoint - func do free double pointers array of strings
 *
 * @p: double pointer to be freed
 *
 * Return: nothing
 */
void free_doubpoint(char **p)
{
	int q, l = 0;

	while (p[l] != 0)
		l++;

	for (q = 0; q < l; q++)
	{
		free(p[q]);
	}
	free(p);
}
/**
 * _copydoublep - func copies Array of Strings
 *
 * @p: double pointer to be copied
 * @old_size: the original size of P
 * @new_size: the size of copy
 *
 * Return: Pointer Malloec
 */
char **_copydoublep(char **p, int old_size, int new_size)
{
	char **copy;
	int q, Csze;

	if (!p && (old_size == new_size))
		return (NULL);

	if (new_size < old_size)
	{
		Csze = new_size;
		copy = malloc(sizeof(char *) * (Csze + 1));
	}
	else
	{
		Csze = old_size;
		copy = malloc(sizeof(char *) * (new_size + 1));
	}
	if (copy == 0)
		return (0);

	if (p)
		for (q = 0; q < Csze; q++)
		{
			copy[q] = _strdup(p[q]);
			if (copy[q] == 0)
			{
				q--;
				for (; q >= 0; q--)
					free(copy[q]);
				free(copy);
				return (0);
			}
		}

	copy[new_size] = '\0';

	return (copy);
}
/**
 * _strlendp - func can calculates length of double pointers
 * @s: the double pointer
 *
 * Return: the Length of double pointers
 *
 */
int _strlendp(char **s)
{
	int q = 0;

	if (!s)
		return (0);

	while (s[q] != NULL)
		q++;
	return (q);
}
/**
 * _setenv - func can Overwrite env variable or create it
 *
 * @env: the array of env variables
 * @variable: the env variable to set
 * @value: the value to be set
 * @shpack: the struct with shell info
 *
 * Return: 0 on success, -1 on error
 */
char **_setenv(char **env, char *variable, char *value, hshpack *shpack)
{
	int q, z, chk, l = 0, lenv1 = 0;
	char *envjoin, *envjoin2, *cpdup, **cp;

	if (_strlen(variable) == 0 || variable == 0)
		return (_error(3, shpack, 1), NULL);
	envjoin2 = str_concat(variable, "=");
	if (envjoin2 == 0)
		return (_error(3, shpack, 1), NULL);
	envjoin = str_concat(envjoin2, value), free(envjoin2);
	if (envjoin == 0)
		return (_error(3, shpack, 1), NULL);
	l = _strlen(variable), lenv1 = _strlendp(env);
	for (q = 0; env && env[q] != 0; q++)
	{
		for (chk = 0, z = 0; z < l && env[q][z] != 0; z++)
		{
			if (variable[z] == '=')
				return (free(envjoin), _error(3, shpack, 2), NULL);
			if (env[q][z] == variable[z])
				chk++;
		}
		if (chk == l && env[q][chk] == '=')
		{
			free(env[q]), cpdup = _strdup(envjoin), free(envjoin);
			if (cpdup == 0)
				return (_error(3, shpack, 1), NULL);
			return (env[q] = cpdup, env);
		}
	}
	cp = _copydoublep(env, lenv1, lenv1 + 1);
	if (env)
		free_doubpoint(env);
	if (cp == 0)
		return (free(envjoin), _error(3, shpack, 1), NULL);
	env = cp, cpdup = _strdup(envjoin), free(envjoin);
	if (cpdup == 0)
		return (_error(3, shpack, 1), NULL);
	return (env[lenv1] = cpdup, env);
}
