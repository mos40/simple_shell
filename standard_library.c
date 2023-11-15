#include "shell.h"

/**
 * isInteractive - determines if shell is in interactive mode
 * @info: Address of a structure
 *
 * Return: 1 if in interactive mode, 0 failure
 */
int isInteractive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_Delim - checks whethera a char is a delimeter
 * @c: the char to be checked
 * @delim: the delimeter str
 * Return: 1 if it is a delimiter, 0 if it is not
 */
int is_Delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isAlpha - Determines if character is alphabetic order
 *@c: The character to be evaluated
 *Return: 1 if "c" is alphabetic, 0 otherwise
 */

int _isAlpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * custom_atoi - converts a str to an integer using the _atoi prototype
 * @s: the string to be proccessed
 * Return: 0 if no numbers found in the str; otherwise the converted int
 */

int custom_atoi(char *s)
{
	int b, signal = 1, flag = 0, output;
	unsigned int result = 0;

	for (b = 0;  s[b] != '\0' && flag != 2; b++)
	{
		if (s[b] == '-')
			signal *= -1;

		if (s[b] >= '0' && s[b] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[b] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (signal == -1)
		output = -result;
	else
		output = result;

	return (output);
}
