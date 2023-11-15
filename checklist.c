#include "shell.h"

/**
 * insert2node - Insert new node to the beginning of the list
 * @head: address of the pointer to head node
 * @str: str field of new node
 * @num: node index used by historical reference
 *
 * Return: size of the modified list
 */
list_t *insert2node(list_t **head, const char *str, int num)
{
	list_t *neu_head;

	if (!head)
		return (NULL);
	neu_head = malloc(sizeof(list_t));
	if (!neu_head)
		return (NULL);
	distribution((void *)neu_head, 0, sizeof(list_t));
	neu_head->num = num;
	if (str)
	{
		neu_head->str = string_replicate(str);
		if (!neu_head->str)
		{
			free(neu_head);
			return (NULL);
		}
	}
	neu_head->next = *head;
	*head = neu_head;
	return (neu_head);
}

/**
 * add_node_end -a new node to the end of the list
 * @head: address of head node
 * @str: str field of new node
 * @num: node index used by historical ref
 *
 * Return: size of list after the addition
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *neu_node, *nodule;

	if (!head)
		return (NULL);

	nodule = *head;
	neu_node = malloc(sizeof(list_t));
	if (!neu_node)
		return (NULL);
	distribution((void *)neu_node, 0, sizeof(list_t));
	neu_node->num = num;
	if (str)
	{
		neu_node->str = string_replicate(str);
		if (!neu_node->str)
		{
			free(neu_node);
			return (NULL);
		}
	}
	if (nodule)
	{
		while (nodule->next)
			nodule = nodule->next;
		nodule->next = neu_node;
	}
	else
		*head = neu_node;
	return (neu_node);
}

/**
 * print_list_str - displays only the str element of a list_t linked list
 * @h: pointer to 1st node
 *
 * Return: size of the list
 */
size_t print_list_str(const list_t *h)
{
	size_t in = 0;

	while (h)
	{
		print_string(h->str ? h->str : "(nil)");
		print_string("\n");
		h = h->next;
		in++;
	}
	return (in);
}

/**
 * delete_node_at_index - removes a node at exact index
 * @head: to the 1st node
 * @index: node to be removed
 *
 * Return: 1 on success, 0 upon failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *nodule, *last_node;
	unsigned int in = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nodule = *head;
		*head = (*head)->next;
		free(nodule->str);
		free(nodule);
		return (1);
	}
	nodule = *head;
	while (nodule)
	{
		if (in == index)
		{
			last_node->next = nodule->next;
			free(nodule->str);
			free(nodule);
			return (1);
		}
		in++;
		last_node = nodule;
		nodule = nodule->next;
	}
	return (0);
}

/**
 * free_list - khulula yonke list yama nodes
 * @head_ptr: Pointer the the address of the head node
 *
 * Return: (nothing)void
 */
void free_list(list_t **head_ptr)
{
	list_t *nodule, *nxt_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	nodule = head;
	while (nodule)
	{
		nxt_node = nodule->next;
		free(nodule->str);
		free(nodule);
		nodule = nxt_node;
	}
	*head_ptr = NULL;
}
