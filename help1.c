#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

/**
 * _puts - func can prints string to std
 * @s: string must be NULL terminated
 *
 * Return: Nothing
 */
void _puts(char *s)
{
	write(1, s, _strlen(s));
}
/**
 * help_exit - func can prints help of exit built in
 *
 * Return: Nothing
 */
void help_exit(void)
{
	_puts("Exit: Exit [n]\n");
	_puts("    quit the shell.\n\n");
	_puts("    quit the shell with status of N.  ");
	_puts("    If N is omitted, the exit status\n");
	_puts("    is that of last command executed.\n");
}
/**
 * help_env - func can prints help of built in
 *
 * Return: Nothing
 */
void help_env(void)
{
	_puts("Env: Env\n");
	_puts("    prints current environment.\n\n");
	_puts("    no options\n");
}
/**
 * help_setenv - func can prints help of setenv built in
 *
 * Return: Nothing
 */
void help_setenv(void)
{
	_puts("Setenv: Setenv [VARIABLE] [VALUE]\n");
	_puts("    start a new environment variable, ");
	_puts("    or modifie existing one.\n\n");
	_puts("    VARIABLE mustn't have character '='.\n");
	_puts("    If no argus are given, setenv prints ");
	_puts("    current environment.\n");
}


/**
 * _help_cmd - func can help of built in commands
 * @shpack: struct has the shell info
 *
 * Return: 1 if succesful, -1 if not
 */
ssize_t _help_cmd(hshpack *shpack)
{
	int check = 1, bcheck = 0;
	helps help[] = {
		{"exit", help_exit},
		{"env", help_env},
		{"setenv", help_setenv},
		{"unsetenv", help_unsetenv},
		{"cd", help_cd},
		{"help", help_help},
		{"alias", help_alias}
	};

	int n = 7;
	int q = 1;

	for (; shpack->options[q]; q++, n = 7)
	{
		while (n--)
			if (!_strcmp(shpack->options[q], help[n].built))
				help[n].h(), bcheck = 1;
	}
	if (shpack->options[1] == NULL)
	{
		printsHelp();
		bcheck = 1;
	}
	if (bcheck == 0)
	{
		check = -1;
		_error(6, shpack, 2);
	}

	free(shpack->options);
	return (check);
}
