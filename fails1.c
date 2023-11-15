#include "shell.h"

/**
 * _erratoi - Function to convert string to an int
 * @s: the input str to be converted
 * Return: 0 if there are no numbers in str, converted number if proccessed
 *       -1 on error code
 */
int _erratoi(char *s)
{
	int in = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;  /* TODO: check why does this causes main return 255? */
	for (in = 0;  s[in] != '\0'; in++)
	{
		if (s[in] >= '0' && s[in] <= '9')
		{
			res *= 10;
			res += (s[in] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - to shows an error message
 * @info: Pointer to the parameter & return info structure
 * @estr: string holding specific error type
 * Return: 0 if numbererror in the str, or converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function that prints a decimal (int) number in base 10
 * @input: to be displayed
 * @fd: the filedescriptor to write to output to
 *
 * Return: number of characters displayed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = write_putchar;
	int in, c = 0;
	unsigned int _abd_, active;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abd_ = -input;
		__putchar('-');
		c++;
	}
	else
		_abd_ = input;
	active = _abd_;
	for (in = 1000000000; in > 1; in /= 10)
	{
		if (_abd_ / in)
		{
			__putchar('0' + active / in);
			c++;
		}
		active %= in;
	}
	__putchar('0' + active);
	c++;

	return (c);
}

/**
 * convert_number - converter function simila to itoa
 * @num: value to be converted
 * @base: base for conversion
 * @flags: flags settings for the conversion
 *
 * Return: string showing the converted value
 */
char *format_number(long int num, int base, int flags)
{
	static char *array;
	static char buffe[50];
	char signal = 0;
	char *tr;
	unsigned long number = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		number = -num;
		signal = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	tr = &buffe[49];
	*tr = '\0';

	do	{
		*--tr = array[number % base];
		number /= base;
	} while (number != 0);

	if (signal)
		*--tr = signal;
	return (tr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: Pointer to the string to be changed
 *
 * Return: Always bring 0 back;
 */
void remove_comments(char *buf)
{
	int in;

	for (in = 0; buf[in] != '\0'; in++)
		if (buf[in] == '#' && (!in || buf[in - 1] == ' '))
		{
			buf[in] = '\0';
			break;
		}
}
