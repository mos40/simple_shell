#include "shell.h"

/**
 * input_buf - buffers chained cmds
 * @info: parameter structure
 * @buf: address of buf
 * @len: address of length var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t res = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buf, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		res = getline(buf, &len_p, stdin);
#else
		res = _getline(info, buf, &len_p);
#endif
		if (res > 0)
		{
			if ((*buf)[res - 1] == '\n')
			{
				(*buf)[res - 1] = '\0'; /* eliminate trailing newline */
				res--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_hist_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = res;
				info->cmd_buf = buf;
			}
		}
	}
	return (res);
}

/**
 * get_input - Retrieves a line without the newline char
 * @info: parameter structure
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buffe; /* the semicolon cmd chain buf */
	static size_t in, join, len_size;
	ssize_t res = 0;
	char **buffe_p = &(info->arg), *p;

	write_putchar(BUF_FLUSH);
	res = input_buf(info, &buffe, &len_size);
	if (res == -1)
		return (-1);
	if (len_size)	/* we have cmds left in the chain buf */
	{
		join = in; /* init new iterator to current buffer position */
		p = buffe + in; /* get pointer for bring back */

		test_chain(info, buffe, &join, in, len_size);
		while (join < len_size) /* iterate to ; or end */
		{
			if (is_info_chain(info, buffe, &join))
				break;
			join++;
		}

		in = join + 1; /* + past nulled semicolon */
		if (in >= len_size) /* reached end of buf? */
		{
			in = len_size = 0; /* reset position and len */
			info->cmd_buf_type = CMD_NORM;
		}

		*buffe_p = p;
		return (str_size(p));
	}

	*buffe_p = buffe;
	return (res);
}

/**
 * read_buf - reads a buf
 * @info: parameter struct
 * @buf: the buffer
 * @i: size
 *
 * Return: res
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t res = 0;

	if (*i)
		return (0);
	res = read(info->readfd, buf, READ_BUF_SIZE);
	if (res >= 0)
		*i = res;
	return (res);
}

/**
 * _getline - gets the following line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buf, preallocated or NULL
 * @length: size of preallocated ptr buf, if is not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffe[READ_BUF_SIZE];
	static size_t in, len_size;
	size_t kick;
	ssize_t res = 0, s = 0;
	char *pe = NULL, *new_ptr = NULL, *c;

	pe = *ptr;
	if (pe && length)
		s = *length;
	if (in == len_size)
		in = len_size = 0;

	res = read_buf(info, buffe, &len_size);
	if (res == -1 || (res == 0 && len_size == 0))
		return (-1);

	c = _strchr(buffe + in, '\n');
	kick = c ? 1 + (unsigned int)(c - buffe) : len_size;
	new_ptr = re_allocate(pe, s, s ? s + kick : kick + 1);
	if (!new_ptr) /* MALLOC ERROR! */
		return (pe ? free(pe), -1 : -1);

	if (s)
		_strncat(new_ptr, buffe + in, kick - in);
	else
		_strncpy(new_ptr, buffe + in, kick - in + 1);

	s += kick - in;
	in = kick;
	pe = new_ptr;

	if (length)
		*length = s;
	*ptr = pe;
	return (s);
}

/**
 * sigintHandler - function that blocks the interruption by hitting ctrl-C
 * @sig_num: the signal no.
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	print_string("\n");
	print_string("$ ");
	write_putchar(BUF_FLUSH);
}
