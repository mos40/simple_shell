#include "shell.h"

/**
 * _myEnviron - prints the active environment
 * @info: Structure holding potential arguments. Used to make
 *          const prototype.
 * Return: Always zeRo
 */
int _myEnviron(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getEnviron - retrieves the value of an environ variable
 * @info: Structure having potential arguments. Used to maintain
 * @name: the name of specified env variable
 *
 * Return: the value of the env var
 */
char *_getEnviron(info_t *info, const char *name)
{
	list_t *nodule = info->env;
	char *v;

	while (nodule)
	{
		v = begins_with(nodule->str, name);
		if (v && *v)
			return (v);
		nodule = nodule->next;
	}
	return (NULL);
}

/**
 * _mysetEnviron - Make a new environment variable or
 *             or change an existing one
 * @info: Struct containing arguments, ensuring a
 *        constant function prototype.
 * Return: Always returns zero
 */
int _mysetEnviron(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetEnviron - Deletes an environment var
 * @info: Structure containing arguments, maintaining
 *        constant function prototype.
 * Return: Always bring back 0
 */
int _myunsetEnviron(info_t *info)
{
	int in;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (in = 1; in <= info->argc; in++)
		_unsetenv(info, info->argv[in]);

	return (0);
}

/**
 * populate_Enviro_list - fills an environment linked list
 * @info: Structure containing potential arguments, taking care
 *          const prototype.
 * Return: Always 0
 */
int populate_Enviro_list(info_t *info)
{
	list_t *node = NULL;
	size_t in;

	for (in = 0; environ[in]; in++)
		add_node_end(&node, environ[in], 0);
	info->env = node;
	return (0);
}
