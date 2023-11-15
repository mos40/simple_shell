#include "shell.h"

/**
 * hsh_structure - primary shell loop
 * @info: the structure holding parameter & return information
 * @av: the array of argument received from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh_structure(info_t *info, char **av)
{
	ssize_t res = 0;
	int builtin_bring = 0;

	while (res != -1 && builtin_bring != -2)
	{
		clear_info(info);
		if (isInteractive(info))
			print_string("$ ");
		_eputchar(BUF_FLUSH);
		res = get_input(info);
		if (res != -1)
		{
			set_info(info, av);
			builtin_bring = detect_built_in(info);
			if (builtin_bring == -1)
				detect_cmd(info);
		}
		else if (isInteractive(info))
			write_putchar('\n');
		free_info(info, 0);
	}
	note_history(info);
	free_info(info, 1);
	if (!isInteractive(info) && info->status)
		exit(info->status);
	if (builtin_bring == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_bring);
}

/**
 * detect_built_in - locate a builtin cmd
 * @info: the struct contains parameter & return information
 *
 * Return: -one if built-in not detected,
 *			0 if builtin cmd is executed successfully,
 *			1 if builtin cmd is found but not successful,
 *			-2 if builtin cmd is signals an exit()
 */
int detect_built_in(info_t *info)
{
	int in, built_in_r = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myEnviron},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetEnviron},
		{"unsetenv", _myunsetEnviron},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (in = 0; builtintbl[in].type; in++)
		if (_str_Cmp(info->argv[0], builtintbl[in].type) == 0)
		{
			info->line_count++;
			built_in_r = builtintbl[in].func(info);
			break;
		}
	return (built_in_r);
}

/**
 * detect_cmd - locates a command in PATH
 * @info: the structure parameter & return data
 *
 * Return: none (void)
 */
void detect_cmd(info_t *info)
{
	char *f_path = NULL;
	int in, kick;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (in = 0, kick = 0; info->arg[in]; in++)
		if (!is_Delim(info->arg[in], " \t\n"))
			kick++;
	if (!kick)
		return;

	f_path = detect_path(info, _getEnviron(info, "PATH="), info->argv[0]);
	if (f_path)
	{
		info->path = f_path;
		fork_child_cmd(info);
	}
	else
	{
		if ((isInteractive(info) || _getEnviron(info, "PATH=")
			|| info->argv[0][0] == '/') && verify_is_cmd(info, info->argv[0]))
			fork_child_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_child_cmd - spawns an exec thread to the run 'cmd' command
 * @info: the parameter & return info structure
 *
 * Return: void
 */
void fork_child_cmd(info_t *info)
{
	pid_t chld_pid;

	chld_pid = fork();
	if (chld_pid == -1)
	{
		/* TODO: Implement the error function */
		perror("Error:");
		return;
	}
	if (chld_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: Implement the error function */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
	}
	}
}
