#include <unistd.h>
#include "shell.h"

/**
 * _getenv - function GETS enviro var
 *
 * @name: the name of enviro var
 * @env: the current environment
 *
 * Return: the P to the value in the enviro,or NULL if no match
 *
 */
char *_getenv(const char *name, char **env)
{
	int q, z, chk, l = 0;

	if (!env)
		return (NULL);

	while (name[l] != 0)
		l++;

	for (q = 0; env[q] != 0; q++)
	{
		for (chk = 0, z = 0; z < l && env[q][z] != 0; z++)
			if (env[q][z] == name[z])
				chk++;
		if (chk == l && env[q][chk] == '=')
			return (env[q]);
	}

	return (NULL);
}
