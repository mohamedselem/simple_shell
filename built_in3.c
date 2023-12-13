#include <limits.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "shell.h"

/**
 * _pow - func do gets the result of base to the ower
 * @base: the base decimal
 * @pot: the power
 *
 * Return: result
 */
long _pow(long base, long pot)
{
	long q = 0;
	long resu = 1;

	for (q = 0; q < pot; q++)
		resu *= base;

	return (resu);
}

/**
 * _atoi - func do convert char input to int
 * @s: the char input
 *
 *
 * Return: the input transformed
 * On error: -1 inapropiate entry
 */

long _atoi(char *s)
{
	long q = 0;
	long h = 0;
	long lens = 0;
	unsigned long result = 0;
	long toRet = 0;
	long minuse = 0;
	long offs = 48;

	if (!s)
		return (0);

	for (q = 0; *(s + q) != '\0'; q++)
	{
		if (*(s + q) >= 48 && *(s + q) <= 57)
			lens++;
		else if (lens != 0)
			break;

		if (*(s + q) == '-')
			minuse++;
	}

	for (q--; lens > 0; q--, h++, lens--)
		result +=  (*(s + q) - offs) * _pow(10, h);

	toRet = (minuse % 2 != 0) ? result * (-1) : result;

	return (toRet);
}
/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 *
 * Return: 0 if strings are equal or another value if not
 *
 */
int _strcmp(char *s1, char *s2)
{
	int q = 0;
	int equal = 0;

	for (q = 0; (*(s1 + q) || *(s2 + q)) && !equal; q++)
		if (*(s1 + q) != *(s2 + q))
			equal = *(s1 + q) - *(s2 + q);

	return (equal);
}
/**
 * _isdigit - checks if a character is a digit
 * @c: character
 *
 * Return: 1 if digit, 0 if not
 *
 */
int _isdigit(int c)
{
	return ((c >= 48 && c <= 57) ? 1 : 0);
}
/**
 * _isnumber - checks if a string is composed of numbers
 * @s: string
 *
 * Return: 1 if string has only numbers, 0 if not
 */
int _isnumber(char *s)
{
	for (; *s; s++)
		if (!_isdigit(*s))
			return (0);
	return (1);
}
