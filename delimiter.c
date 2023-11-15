#include "shell.h"

/**
 * **strt - divided a string into words and ignore duplicated are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL in case failure
 */

char **strt(char *str, char *d)
{
	int in, ju, kick, em, sumwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (in = 0; str[in] != '\0'; in++)
		if (!is_Delim(str[in], d) && (is_Delim(str[in + 1], d) || !str[in + 1]))
			sumwords++;

	if (sumwords == 0)
		return (NULL);
	s = malloc((1 + sumwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (in = 0, ju = 0; ju < sumwords; ju++)
	{
		while (is_Delim(str[in], d))
			in++;
		kick = 0;
		while (!is_Delim(str[in + kick], d) && str[in + kick])
			kick++;
		s[ju] = malloc((kick + 1) * sizeof(char));
		if (!s[ju])
		{
			for (kick = 0; kick < ju; kick++)
				free(s[kick]);
			free(s);
			return (NULL);
		}
		for (em = 0; em < kick; em++)
			s[ju][em] = str[in++];
		s[ju][em] = 0;
	}
	s[ju] = NULL;
	return (s);
}

/**
 * **strt2 - divides a string into words
 * @str: the input str
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL incase of failure
 */
char **strt2(char *str, char d)
{
	int in, ju, kick, my, sum_words = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (in = 0; str[in] != '\0'; in++)
		if ((str[in] != d && str[in + 1] == d) ||
		    (str[in] != d && !str[in + 1]) || str[in + 1] == d)
			sum_words++;
	if (sum_words == 0)
		return (NULL);
	st = malloc((1 + sum_words) * sizeof(char *));
	if (!st)
		return (NULL);
	for (in = 0, ju = 0; ju < sum_words; ju++)
	{
		while (str[in] == d && str[in] != d)
			in++;
		kick = 0;
		while (str[in + kick] != d && str[in + kick] && str[in + kick] != d)
			kick++;
		st[ju] = malloc((kick + 1) * sizeof(char));
		if (!st[ju])
		{
			for (kick = 0; kick < ju; kick++)
				free(st[kick]);
			free(st);
			return (NULL);
		}
		for (my = 0; my < kick; my++)
			st[ju][my] = str[in++];
		st[ju][my] = 0;
	}
	st[ju] = NULL;
	return (st);
}
