#include "shell.h"

/**
 * str_size - calculate the length of a string
 * @s: the string for which to check the length
 *
 * Return: int taken place for the linear measure of a string
 */
int str_size(char *s)
{
	int in = 0;

	if (!s)
		return (0);

	while (*s++)
		in++;
	return (in);
}

/**
 * _str_Cmp - Compare 2 string lexicogarphically
 * @s1: the 1st string
 * @s2: the 2nd string
 *
 * Return: negative val if s1 < s2, positive val if s1 > s2,0 if s1 == s2
 */
int _str_Cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * begins_with - checks if haystack begins with the needle
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next character in haystack or NULL if not found
 */
char *begins_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _str_Cat - combines two strings
 * @dest: the target buffer for destination
 * @src: the source buffer to append.
 *
 * Return: pointer to dest buffer
 */
char *_str_Cat(char *dest, char *src)
{
	char *bring = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (bring);
}
