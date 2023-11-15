#include "shell.h"

/**
 *_eputs - prints an input str to the standard output
 * @str: the cstring to be displayed
 *
 * Return: it doesnt bring any value back
 */
void _eputs(char *str)
{
	int in = 0;

	if (!str)
		return;
	while (str[in] != '\0')
	{
		_eputchar(str[in]);
		in++;
	}
}

/**
 * _eputchar - writes the given character c to standard err stream
 * @c: The character to show
 *
 * Return: On success return 1
 * On error, -1 is returned, & sets errno appropriately.
 */
int _eputchar(char c)
{
	static int in;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || in >= WRITE_BUF_SIZE)
	{
		write(2, buff, in);
		in = 0;
	}
	if (c != BUF_FLUSH)
		buff[in++] = c;
	return (1);
}

/**
 * _putfd - writes the character "c" to the specified fd
 * @c: The cstring character to be written
 * @fd: The file descriptor to printed to
 *
 * Return: On success bring 1 back
 * On error, it returns -1, &errno is set the appropriately errno.
 */
int _putfd(char c, int fd)
{
	static int in;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || in >= WRITE_BUF_SIZE)
	{
		write(fd, buff, in);
		in = 0;
	}
	if (c != BUF_FLUSH)
		buff[in++] = c;
	return (1);
}

/**
 *_putsfd - prints a string to a file descriptor
 * @str: the cstring to be displayed
 * @fd: the fd to write to
 *
 * Return: the number of cstrings & chars written
 */
int _putsfd(char *str, int fd)
{
	int in = 0;

	if (!str)
		return (0);
	while (*str)
	{
		in += _putfd(*str++, fd);
	}
	return (in);
}
