#include "shell.h"

/**
 * bfree - release memory with a pointer and set it to NULLs the address
 * @ptr: address of the pointer to release
 *
 * Return: 1 if successfully released, else 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
