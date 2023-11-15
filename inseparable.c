#include "shell.h"

/**
 * _myhistory - This fun prints the hist_list, 1 cmd by line, along
 *              with line numbers, beginning at 0.
 * @info: Structure that holds potential argc & maintains a constant.
 * Return: this prototype is always bring back 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Assigns str alias to an alias var
 * @info: the parameter structure
 * @str: the string representing the alias
 *
 * Return: Always 0 on success, 1 on error code
 */
int unset_alias(info_t *info, char *str)
{
	char *w, i;
	int bring;

	w = _strchr(str, '=');
	if (!w)
		return (1);
	i = *w;
	*w = 0;
	bring = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*w = i;
	return (bring);
}

/**
 * set_alias - Assigns an alias to str
 * @info: A parameter structure
 * @str: the string is representing the alias
 *
 * Return: Always 0 on success, 1 on error code
 */
int set_alias(info_t *info, char *str)
{
	char *w;

	w = _strchr(str, '=');
	if (!w)
		return (1);
	if (!*++w)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Displays the content of an alias str
 * @node: the alias node contains the str
 *
 * Return: Always 0 on success, 1 on error code
 */
int print_alias(list_t *node)
{
	char *w = NULL, *f = NULL;

	if (node)
	{
		w = _strchr(node->str, '=');
		for (f = node->str; f <= w; f++)
			write_putchar(*f);
		write_putchar('\'');
		print_string(w + 1);
		print_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Emulates the act of the alias built-in cmd (see man alias)
 * @info: Structure hold optional argc & maintain constant function prototype.
 *  Return: THis function always on 0
 */
int _myalias(info_t *info)
{
	int in = 0;
	char *w = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (in = 1; info->argv[in]; in++)
	{
		w = _strchr(info->argv[in], '=');
		if (w)
			set_alias(info, info->argv[in]);
		else
			print_alias(node_starts_with(info->alias, info->argv[in], '='));
	}

	return (0);
}
