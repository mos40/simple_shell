#include "shell.h"

/**
 * main - The main prototype serves as the entry point
 * @ac: Arg_count
 * @av: Arg_vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t data[] = {DEFAULT_INIT};
	int filed = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (filed)
		: "r" (filed));

	if (ac == 2)
	{
		filed = open(av[1], O_RDONLY);
		if (filed == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readfd = filed;
	}
	populate_Enviro_list(data);
	read_hist(data);
	hsh_structure(data, av);
	return (EXIT_SUCCESS);
}
