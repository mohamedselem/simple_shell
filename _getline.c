#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BSIZE 4
/**
 * _memset - function fills the memory with constant bytes
 * @s: the memory area
 * @b: the constant byte b
 * @n: the first n bytes of memory area pointed by s
 *
 * Return: On success 1.
 * On error, -1 is returned, and error is set appropre.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int q;

	for (q = 0; q < n; q++)
		s[q] = b;
	return (s);
}
/**
 * _memcpy - func copies Memory
 * @dest: the destination
 * @src: the source
 * @n: size of memory to be copied
 *
 * Return: Returns memory that Copied
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int q;

	for (q = 0; q < n; q++)
		dest[q] = src[q];
	return (dest);
}
/**
 * _realloc - func do reallocate memory block using malloc
 * @ptr: the pointer to be modify
 * @old_size: the current size of memory
 * @new_size: the size memory will now have it
 *
 * Return: Pointer to the reallocated memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *PTR3;

	if (old_size == new_size)
		return (ptr);

	if (ptr == NULL)
	{
		PTR3 = malloc(new_size);
		if (PTR3 == 0)
			return (0);
		free(ptr);
		return (PTR3);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (0);
	}

	PTR3 = malloc(new_size);

	if (PTR3 == 0)
		return (0);

	PTR3 = _memset(PTR3, '\0', new_size);

	_memcpy(PTR3, ptr, old_size);
	free(ptr);
	return (PTR3);
}
/**
 * _getline - FUNC DO read a string or a line from input
 * @buffer: the pointer to space where STDIN read will saved as string
 * @bufsize: the current size of buffer
 * @fd: stream to read
 *
 * Return: Number of CHRACS Read
 */
int _getline(char **buffer, size_t *bufsize, int fd)
{
	static char *bff;
	static size_t size;
	unsigned int len1 = 0, q = 0, sizeold;
	int z;

	if (*bufsize == 0)
		size = BSIZE;
	if (*buffer == 0)
	{
		bff = malloc(sizeof(char) * size);
		if (!bff)
			return (write(2, "Memory Error", 22), 0);
		*buffer = bff;
	}
	bff = _memset(bff, '\0', size);
	do {

		z = read(fd, bff + len1, BSIZE);
		if (z >= 0)
			q = len1, len1 += z;
		if (z == -1 || z == 0)
			return (-1);
		if  (len1 >= size)
		{
			sizeold = size, size += BSIZE;
			bff = _realloc(bff, sizeold, size);
			if (!bff)
				return (write(2, "Memory Error", 22), 0);
		}
		for (; q < len1; q++)
		{
			if (bff[q] == '\n')
			{
				*buffer = bff, *bufsize = size;
				return (len1);
			}
		}

	} while (1);
	return (len1);
}
