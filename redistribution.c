#include "shell.h"

/**
 * distribution - set a constant byte in a memory area
 * @s: Ptr to the storage area
 * @b: the byte to fill the storage
 * @n: the sum of bytes to be filled
 * Return: a pointer to the storage area
 */
char *distribution(char *s, char b, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
		s[index] = b;
	return (s);
}

/**
 * filefree - releases a str of strings
 * @pp: string of strings to be released
 */
void filefree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * re_allocate - reallocates a  memory block
 * @ptr: pointer to last malloc'ated block
 * @old_size: byte size in bytes of the previous block
 * @new_size: byte size in bytes of new block
 *
 * Return: pointer to the changed memory block
 */
void *re_allocate(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
