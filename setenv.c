#include "shell.h"

/**
 * get_environ - brings back a copy of the str array holing env variables
 * @info: Structure having additional info. Used to maintain
 *          constant function prototype.
 * Return: Always bring 0 zero
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Deletes an environment var
 * @info: Structure containing additional arguments & maintain
 *        constant function prototype.
 *  Return: 1 if the var is deleted, 0 otherwise
 * @var: the string showing the env variable property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *nodule = info->env;
	size_t in = 0;
	char *pr;

	if (!nodule || !var)
		return (0);

	while (nodule)
	{
		pr = begins_with(nodule->str, var);
		if (pr && *pr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), in);
			in = 0;
			nodule = info->env;
			continue;
		}
		nodule = nodule->next;
		in++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Modify a new env variable
 * or initialise an existing one
 * @info: Structure containing arguments and to maintain
 * constant prototype.
 * @var: the string representing env variable property
 * @value: the string representing env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *nodule;
	char *pr;

	if (!var || !value)
		return (0);

	buff = malloc(str_size(var) + str_size(value) + 2);
	if (!buff)
		return (1);
	string_copy(buff, var);
	_str_Cat(buff, "=");
	_str_Cat(buff, value);
	nodule = info->env;
	while (nodule)
	{
		pr = begins_with(nodule->str, var);
		if (pr && *pr == '=')
		{
			free(nodule->str);
			nodule->str = buff;
			info->env_changed = 1;
			return (0);
		}
		nodule = nodule->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
