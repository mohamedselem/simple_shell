#include <stdlib.h>
#include "shell.h"

/**
 * _strcpy - copy the source input int the destinated input
 * @dest: target the place will be stored the input
 * @src: source to the copy from
 *
 *
 * Return: destination address
 * On error: -1 wrong entry
 */

char *_strcpy(char *dest, char *src)
{
	int n = 0;

	for (n = 0; *(src + n) != '\0'; n++)
		*(dest + n) = *(src + n);

	*(dest + n) = *(src + n); 

	return (dest);
}

/**
 * _strlen - function can returns the length of string
 * @s: the string address
 *
 *
 * Return: nothing
 * On error: -1 wrong entry
 */

int _strlen(char *s)
{
	return ((!*s) ? 0 : 1 + _strlen(s + 1));
}

/**
 * _strdup - function that returns a pointer to new allocated
 * in memory contains copy of the string given as a parameter
 * @str: source to copy
 *
 *
 * Return: address where is the result
 * On error: -1 inapropiate entry
 */

char *_strdup(char *str)
{
	char *asr;

	if (!str)
		return (NULL);

	asr = malloc((_strlen(str) * sizeof(*asr)) + 1);

	if (!asr)
		return (NULL);

	_strcpy(asr, str);

	return (asr);
}
