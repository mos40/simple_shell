#include "shell.h"

/**
 * string_copy - function prototype copies a str
 * @dest: Pointer to the dest
 * @src: pointer to the source
 *
 * Return: pointer to the destination
 */
char *string_copy(char *dest, char *src)
{
	int in = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[in])
	{
		dest[in] = src[in];
		in++;
	}
	dest[in] = 0;
	return (dest);
}

/**
 * string_replicate - function that replicates a string
 * @str: the cstring to be replicated
 *
 * Return: pointer to the replicated string
 */
char *string_replicate(const char *str)
{
	int length_s = 0;
	char *bring;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length_s++;
	bring = malloc(sizeof(char) * (length_s + 1));
	if (!bring)
		return (NULL);
	for (length_s++; length_s--;)
		bring[length_s] = *--str;
	return (bring);
}

/**
 * print_string - prototype prints an input string
 * @str: the cstring to be displayed
 *
 * Return: Nothing, no explicit return value
 */
void print_string(char *str)
{
	int in = 0;

	if (!str)
		return;
	while (str[in] != '\0')
	{
		write_putchar(str[in]);
		in++;
	}
}

/**
 * write_putchar - prototype that writes the char c to stdout
 * @c: The character to display
 *
 * Return: On success 1.
 */
int write_putchar(char c)
{
	static int in;
	static char buffe[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || in >= WRITE_BUF_SIZE)
	{
		write(1, buffe, in);
		in = 0;
	}
	if (c != BUF_FLUSH)
		buffe[in++] = c;
	return (1);
}
