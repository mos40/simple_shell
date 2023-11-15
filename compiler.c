#include "shell.h"

/**
 * verify_is_cmd - function to check a if the file is an executable cmd
 * @info: the dats struct
 * @path: path to the file
 *
 * Return: 1 if it is an exe cmd true, 0 otherwise
 */
int verify_is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * doubles_chars - doubles & create a range of  char from a provided path str
 * @pathstr: the PATH str
 * @start: start index
 * @stop: end index
 *
 * Return: pointer to new buffer containing the doubled charrs
 */
char *doubles_chars(char *pathstr, int start, int stop)
{
	static char buffe[1024];
	int inside = 0, k = 0;

	for (k = 0, inside = start; inside < stop; inside++)
		if (pathstr[inside] != ':')
			buffe[k++] = pathstr[inside];
	buffe[k] = 0;
	return (buffe);
}

/**
 * detect_path - Locates exact this cmd within the PATH string
 * @info: the data struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find/locate
 *
 * Return: full path of cmd if found or NULL if not found.
 */
char *detect_path(info_t *info, char *pathstr, char *cmd)
{
	int in = 0, current_p = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((str_size(cmd) > 2) && begins_with(cmd, "./"))
	{
		if (verify_is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[in] || pathstr[in] == ':')
		{
			path = doubles_chars(pathstr, current_p, in);
			if (!*path)
				_str_Cat(path, cmd);
			else
			{
				_str_Cat(path, "/");
				_str_Cat(path, cmd);
			}
			if (verify_is_cmd(info, path))
				return (path);
			if (!pathstr[in])
				break;
			current_p = in;
		}
		in++;
	}
	return (NULL);
}
