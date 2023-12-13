#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "shell.h"

/**
 * rev_str - function of Reverses a String
 * @s: the string will be reverse
 *
 * Return: Nothing
 */
void rev_str(char *s)
{
	int q = 0, z = 0, l;
	char TP;

	while (s[q])
		q++;
	l = q / 2, q = q - 1;
	while (q >= l)
	{
		TP  = s[z];
		s[z] = s[q];
		s[q] = TP;
		q--, z++;
	}
}
/**
 * blen - function to obtains length of number in base
 *
 * @n: numbers
 * @base: base of numbers
 *
 * Return: length of numbers
 */
int blen(unsigned long int n, unsigned long int base)
{
	unsigned long int q, NG = 0;

	for (q = 0; n > 0; q++)
		n = n / base;
	return (q + NG);
}
/**
 * _itoa - function to converts integer to string
 *
 * @n: the number
 *
 * Return: the pointer to string
 */
char *_itoa(int n)
{
	unsigned long int q = 0, BS = 10;
	char *str;

	if (n != 0)
		str = malloc(blen(n, BS) + 1);
	else
		str = malloc(2), str[q] = '0', q++;

	if (str == 0)
		return (0);

	for (; n > 0; q++)
	{
		str[q] = (n % BS) + '0';
		n = n / BS;
	}
	str[q] = '\0';
	rev_str(str);
	return (str);
}

char *_error2(int errn, char *conc2, char *option);
/**
 * _error - function to create string with ERR line
 * @errn: the number respond to types of error
 * @shpack: the struct which containing shell info
 * @exnum: the value of exit shell should have
 *
 * Return: 0 success, -1 fail
 */
int _error(int errn, hshpack *shpack, int exnum)
{

	int cont = shpack->errnum[0], l = 0;
	char *cmd = shpack->cmd, **option = shpack->options;
	char *shelln = shpack->hshname;
	char *nstring, *conc1, *conc2, *colspace = ": ";
	char *err[] = {
		"Not fOund", "PErmission DEnied", "Illegal Number",
		"Name is NULL, Points TO String of len 0, or has an '=' char.",
		"can't CD to ", "Illegal option ", "Help command error",
		"Error Allocating memory", "Wrong Alias",
		NULL
	};

	conc1 = str_concat(shelln, colspace);
	if (!conc1)
		return (write(2, "Memory Error", 22), -1);

	if (errn == 7)
	{
		conc2 = str_concat(conc1, err[errn]);
		if (!conc2)
			return (free(conc1), write(2, "Memory Error", 22), -1);
		free(conc1);
		while (conc2[l] != 0)
			l++;
		write(2, conc2, l), write(2, "\n", 1);
		free(conc2);
		return (0);

	}

	nstring = _itoa(cont);
	if (!nstring)
		return (free(conc1), write(2, "Memory Error", 22), -1);

	conc2 = str_concat(conc1, nstring);
	if (!conc2)
	{
		write(2, "Memory Error", 22);
		return (free(conc1), free(nstring),  -1);
	}
	free(conc1), free(nstring);

	conc1 = str_concat(conc2, colspace);
	if (!conc1)
		return (free(conc2), write(2, "Memory Error", 22), -1);

	free(conc2);
	conc2 = str_concat(conc1, cmd);
	if (!conc2)
		return (free(conc1), write(2, "Memory Error", 22), -1);
	free(conc1);

	conc1 = str_concat(conc2, colspace);
	if (!conc1)
		return (free(conc2), write(2, "Memory Error", 22), -1);
	free(conc2);

	conc2 = str_concat(conc1, err[errn]);
	if (!conc2)
		return (free(conc1), write(2, "Memory Error", 22), -1);
	free(conc1);

	if (errn > 1 && errn < 6 && errn != 3)
		conc2 = _error2(errn, conc2, option[1]);
	if (conc2 == NULL)
	{
		write(2, "Memory Error", 22);
		return (-1);
	}

	while (conc2[l] != 0)
		l++;
	write(2, conc2, l), write(2, "\n", 1);
	free(conc2);
	shpack->exitnum[0] = exnum;
	return (0);

}
/**
 * _error2 - the extra modes for ERR generate
 * @errn: the number responding to types of errors
 * @conc2: the error part from _error
 * @option: CMD options
 *
 * Return: the pointer to string
 */
char *_error2(int errn, char *conc2, char *option)
{

	char *conc1, *colspace = ": ";

	if (errn == 2)
	{

		conc1 = str_concat(conc2, colspace);
		if (!conc1)
		{
			write(2, "Memory Error", 22);
			return (free(conc2), NULL);
		}
		free(conc2);

		conc2 = str_concat(conc1, option);

		if (!conc2)
		{
			write(2, "Memory Error", 22);
			return (free(conc1), NULL);
		}
		free(conc1);
	}
	if (errn > 3)
	{
		conc1 = str_concat(conc2, option);
		if (!conc1)
		{
			write(2, "Memory Error", 22);
			return (free(conc2), NULL);
		}
		free(conc2);
		return (conc1);
	}
	return (conc2);

}
