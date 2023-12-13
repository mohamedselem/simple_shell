#include <stdlib.h>
#include "shell.h"

/**
 * str_concat - func concatenate two strings
 * @s1: string1
 * @s2: string2
 *
 * Return: the Pointer
 */
char *str_concat(char *s1, char *s2)
{
	int l1, l2, q, n;
	char *s;
	char *nul = "";

	if (s1 == NULL)
		s1 = nul;
	if (s2 == NULL)
		s2 = nul;

	l1 = 0, l2 = 0;
	while (*(s1 + l1))
		l1++;
	while (*(s2 + l2))
		l2++;

	s = malloc(sizeof(char) * (l1 + l2 + 1));

	if (s == 0)
		return (0);

	for (q = 0; q < l1; q++)
		*(s + q) = *(s1 + q);

	for (q = 0, n = l1; q <= l2; n++, q++)
		*(s + n) = *(s2 + q);

	return (s);
}
