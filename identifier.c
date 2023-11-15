#include "shell.h"

/**
 * is_info_chain - checks whether current char in buf is a chain delimeter
 * @info: the parameter structure
 * @buf: the char buf
 * @p: address of present position in buf
 *
 * Return: 1 if it's a chain delimeter, 0 otherwise
 */
int is_info_chain(info_t *info, char *buf, size_t *p)
{
	size_t ju = *p;

	if (buf[ju] == '|' && buf[ju + 1] == '|')
	{
		buf[ju] = 0;
		ju++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[ju] == '&' && buf[ju + 1] == '&')
	{
		buf[ju] = 0;
		ju++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[ju] == ';') /* detected the end of this command */
	{
		buf[ju] = 0; /* substitute semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = ju;
	return (1);
}

/**
 * test_chain - find  whether we should continue chaining on last status
 * @info: the parameter struct
 * @buf: the character buf
 * @p: address of active position in buffer
 * @i: beginning of position in buf
 * @len: size of buffer
 *
 * Return: Void
 */
void test_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t ju = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			ju = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			ju = len;
		}
	}

	*p = ju;
}

/**
 * restore_alias - substitutes an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if substituted, 0 otherwise
 */
int restore_alias(info_t *info)
{
	int inside;
	list_t *nodule;
	char *ptr;

	for (inside = 0; inside < 10; inside++)
	{
		nodule = node_starts_with(info->alias, info->argv[0], '=');
		if (!nodule)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(nodule->str, '=');
		if (!ptr)
			return (0);
		ptr = string_replicate(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * restore_vars - substitutes vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if substitutes, 0 otherwise
 */
int restore_vars(info_t *info)
{
	int in = 0;
	list_t *nodule;

	for (in = 0; info->argv[in]; in++)
	{
		if (info->argv[in][0] != '$' || !info->argv[in][1])
			continue;

		if (!_str_Cmp(info->argv[in], "$?"))
		{
			restore_string(&(info->argv[in]),
				string_replicate(format_number(info->status, 10, 0)));
			continue;
		}
		if (!_str_Cmp(info->argv[in], "$$"))
		{
			restore_string(&(info->argv[in]),
				string_replicate(format_number(getpid(), 10, 0)));
			continue;
		}
		nodule = node_starts_with(info->env, &info->argv[in][1], '=');
		if (nodule)
		{
			restore_string(&(info->argv[in]),
				string_replicate(_strchr(nodule->str, '=') + 1));
			continue;
		}
		restore_string(&info->argv[in], string_replicate(""));

	}
	return (0);
}

/**
 * restore_string - substitutes string
 * @old: address of old string
 * @new: new str
 *
 * Return: 1 if substituted, 0 otherwise
 */
int restore_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
