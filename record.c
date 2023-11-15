#include "shell.h"

/**
 * get_hist_file - finds the hist_file
 * @info: parameter structure
 *
 * Return: allocated string holding history file
 */

char *get_hist_file(info_t *info)
{
	char *buffe, *home_dir;

	home_dir = _getEnviron(info, "HOME=");
	if (!home_dir)
		return (NULL);
	buffe = malloc(sizeof(char) * (str_size(home_dir) + str_size(HIST_FILE) + 2));
	if (!buffe)
		return (NULL);
	buffe[0] = 0;
	string_copy(buffe, home_dir);
	_str_Cat(buffe, "/");
	_str_Cat(buffe, HIST_FILE);
	return (buffe);
}

/**
 * note_history - generates a new file/appends to an existing one
 * @info: the parameter struct
 *
 * Return: 1 on success, error on -1
 */
int note_history(info_t *info)
{
	ssize_t filed;
	char *fileName = get_hist_file(info);
	list_t *nodule = NULL;

	if (!fileName)
		return (-1);

	filed = open(fileName, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fileName);
	if (filed == -1)
		return (-1);
	for (nodule = info->history; nodule; nodule = nodule->next)
	{
		_putsfd(nodule->str, filed);
		_putfd('\n', filed);
	}
	_putfd(BUF_FLUSH, filed);
	close(filed);
	return (1);
}

/**
 * read_hist - reads history from a file
 * @info: the parameter structure
 *
 * Return: histcount on success, 0 in case of otherwise
 */
int read_hist(info_t *info)
{
	int in, las = 0, lineCount = 0;
	ssize_t filed, rdlen, f_size = 0;
	struct stat st;
	char *buffe = NULL, *fileName = get_hist_file(info);

	if (!fileName)
		return (0);

	filed = open(fileName, O_RDONLY);
	free(fileName);
	if (filed == -1)
		return (0);
	if (!fstat(filed, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buffe = malloc(sizeof(char) * (f_size + 1));
	if (!buffe)
		return (0);
	rdlen = read(filed, buffe, f_size);
	buffe[f_size] = 0;
	if (rdlen <= 0)
		return (free(buffe), 0);
	close(filed);
	for (in = 0; in < f_size; in++)
		if (buffe[in] == '\n')
		{
			buffe[in] = 0;
			build_hist_list(info, buffe + las, lineCount++);
			las = in + 1;
		}
	if (las != in)
		build_hist_list(info, buffe + las, lineCount++);
	free(buffe);
	info->histcount = lineCount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	new_number_hist(info);
	return (info->histcount);
}

/**
 * build_hist_list - Appends an entry to a history linked list
 * @info: Structure that may have arguments for maintainance
 * @buf: buffer
 * @linecount: the history line count and histcount
 *
 * Return: Always 0
 */
int build_hist_list(info_t *info, char *buf, int linecount)
{
	list_t *nodule = NULL;

	if (info->history)
		nodule = info->history;
	add_node_end(&nodule, buf, linecount);

	if (!info->history)
		info->history = nodule;
	return (0);
}

/**
 * new_number_hist - updates the historical linked list after changes
 * @info: Structure that contain potential arguments for maintainance
 *
 * Return: the new histcount value
 */
int new_number_hist(info_t *info)
{
	list_t *nodule = info->history;
	int i = 0;

	while (nodule)
	{
		nodule->num = i++;
		nodule = nodule->next;
	}
	return (info->histcount = i);
}
