#include "shell.h"

/**
 * list_len - count_the size of a linked list
 * @h: pointer to 1st node
 *
 * Return: length of list
 */
size_t list_len(const list_t *h)
{
	size_t in = 0;

	while (h)
	{
		h = h->next;
		in++;
	}
	return (in);
}

/**
 * list_to_strings - generate an array of strings from of the list->str
 * @head: 1st node in the list at the pointer
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *nodule = head;
	size_t in = list_len(head), jr;
	char **strngs;
	char *strng;

	if (!head || !in)
		return (NULL);
	strngs = malloc(sizeof(char *) * (in + 1));
	if (!strngs)
		return (NULL);
	for (in = 0; nodule; nodule = nodule->next, in++)
	{
		strng = malloc(str_size(nodule->str) + 1);
		if (!strng)
		{
			for (jr = 0; jr < in; jr++)
				free(strngs[jr]);
			free(strngs);
			return (NULL);
		}

		strng = string_copy(strng, nodule->str);
		strngs[in] = strng;
	}
	strngs[in] = NULL;
	return (strngs);
}


/**
 * print_list - Displays all elements of the list_t linked list
 * @h: first node in the list
 *
 * Return: size of list and array strings
 */
size_t print_list(const list_t *h)
{
	size_t in = 0;

	while (h)
	{
		print_string(convert_number(h->num, 10, 0));
		write_putchar(':');
		write_putchar(' ');
		print_string(h->str ? h->str : "(nil)");
		print_string("\n");
		h = h->next;
		in++;
	}
	return (in);
}

/**
 * node_starts_with - Letha node nama string begins with prefix
 * @node: pointer to list's head
 * @prefix: string to match as the prefix
 * @c: the char immediately prefix to match
 *
 * Return: match node or null if on found
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *pfx = NULL;

	while (node)
	{
		pfx = begins_with(node->str, prefix);
		if (pfx && ((c == -1) || (*pfx == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Fiinds the index of a node within a list
 * @head: pointer to list's head
 * @node: pointer to the node of interest
 *
 * Return: index of node or -1 if not found
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t in = 0;

	while (head)
	{
		if (head == node)
			return (in);
		head = head->next;
		in++;
	}
	return (-1);
}
