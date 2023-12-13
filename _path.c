#include "shell.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * _pathcheck - func do check if current directory must be added
 * @path: the path env variable
 *
 * Return: the Pointer to address of new PATH
 *
 */

char *_pathcheck(char *path)
{
	char *npth;
	int q, z, nsze, count = 0;

	for (q = 0; path[q]; q++)
	{

		if (path[q] == '=' && path[q + 1] == ':')
			count++;
		if (path[q] == ':' && path[q + 1] == ':')
			count++;
		if (path[q] == ':' && path[q + 1] == '\0')
			count++;
	}
	if (count == 0)
		return (0);
	nsze = _strlen(path) + 1 + count;
	npth = malloc(sizeof(char) * nsze);

	for (q = 0, z = 0; q < nsze; q++, z++)
	{
		if (path[z] == '=' && path[z + 1] == ':')
		{
			npth[q] = path[z], npth[q + 1] = '.', q++;
			continue;
		}
		if (path[z] == ':' && path[z + 1] == ':')
		{
			npth[q] = path[z], npth[q + 1] = '.', q++;
			continue;
		}
		if (path[z] == ':' && path[z + 1] == '\0')
		{
			npth[q] = path[z], npth[q + 1] = '.', q++;
			continue;
		}
		npth[q] = path[z];
	}
	free(path);
	return (npth);
}
/**
 * _path - fun can Searches for CMD in PATH
 * @cmd: the string contating env var PATH
 * @env: current envir
 * @shpack: struct containing shell inforomation
 *
 * Return: the Pointer to adress of CMD in PATH
 *
 */

char *_path(char *cmd, char **env, hshpack *shpack)
{
	char *pth1, *pth2;
	struct stat st2;
	char *TKN, *concat, *concat2, *pathcheck, *dlim = ":=";
	int i;

	for (i = 0; cmd[i]; i++)
		if (cmd[i] == '/')
		{
			if (stat(cmd, &st2) == 0)
				return (concat = str_concat(cmd, '\0'));
			else
				return (0);
		}

	pth2 = _getenv("PATH", env);
	(void) shpack;
	if (!pth2)
		return (0);
	pth1 = _strdup(pth2);
	pathcheck = _pathcheck(pth1);
	if (pathcheck)
		pth1 = pathcheck;
	TKN = _strtok(pth1, dlim);
	for (TKN = _strtok(0, dlim); TKN; TKN = _strtok(0, dlim))
	{
		concat = str_concat(TKN, "/");
		concat2 = str_concat(concat, cmd);
		free(concat);
		if (stat(concat2, &st2) == 0)
		{
			free(pth1);
			return (concat2);
		}
		free(concat2);
	}

	free(pth1);
	return (0);
}
