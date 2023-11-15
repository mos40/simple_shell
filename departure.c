#include "shell.h"

/**
 * _strncpy - copy a str
 * @dest: the dest string to be copied to
 * @src: the src string
 * @n: the number of chars to be copied
 * Return: A concatenated str
 */
char *_strncpy(char *dest, char *src, int n)
{
	int in, jay;
	char *see = dest;

	in = 0;
	while (src[in] != '\0' && in < n - 1)
	{
		dest[in] = src[in];
		in++;
	}
	if (in < n)
	{
		jay = in;
		while (jay < n)
		{
			dest[jay] = '\0';
			jay++;
		}
	}
	return (see);
}

/**
 **_strncat - concatenates 2 strings
 *@dest: the 1st string
 *@src: the 2nd string
 *@n: the max number of bytes to be maximally used
 *Return: the concatenated str
 */
char *_strncat(char *dest, char *src, int n)
{
	int in, jay;
	char *see = dest;

	in = 0;
	jay = 0;
	while (dest[in] != '\0')
		in++;
	while (src[jay] != '\0' && jay < n)
	{
		dest[in] = src[jay];
		in++;
		jay++;
	}
	if (jay < n)
		dest[in] = '\0';
	return (see);
}

/**
 **_strchr - Finds a char in a string
 *@s: the str to be parsed
 *@c: the character to see for
 *Return: the memory area
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
