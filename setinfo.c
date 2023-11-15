#include "shell.h"

/**
 * clear_info - initializes an info_t structure
 * @info: Pointer to the struct
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - change an info_t struct
 * @info: struct to address
 * @av: arg vector
 */
void set_info(info_t *info, char **av)
{
	int in = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strt(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = string_replicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (in = 0; info->argv && info->argv[in]; in++)
			;
		info->argc = in;

		restore_alias(info);
		restore_vars(info);
	}
}

/**
 * free_info - releases of an info_t struct fields
 * @info: struct address
 * @all: true if releasing all fields
 */
void free_info(info_t *info, int all)
{
	filefree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		filefree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		write_putchar(BUF_FLUSH);
	}
}
