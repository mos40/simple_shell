#include "shell.h"

/**
 * _myexit - Prototype for exiting a shell
 * @info: A struct holding arguments. It is used to ensure a
 *          constant function prototype.
 * Return: exits the shell with a given exit status
 *         (0) if info.argv[0] is not equal to "exit"
 */
int _myexit(info_t *info)
{
	int exit_check;

	if (info->argv[1])  /* If there is an exit arg */
	{
		exit_check = _erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Modifies the present dir of the process
 * @info: Structure holding arguments. Used to ensure a
 *          constant function prototype.
 *  Return: Always bring back 0
 */
int _mycd(info_t *info)
{
	char *set, *d, buf[1024];
	int chdir_bring;

	set = getcwd(buf, 1024);
	if (!set)
		print_string("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		d = _getEnviron(info, "HOME=");
		if (!d)
			chdir_bring = /* TODO: what should this represent? */
				chdir((d = _getEnviron(info, "PWD=")) ? d : "/");
		else
			chdir_bring = chdir(d);
	}
	else if (_str_Cmp(info->argv[1], "-") == 0)
	{
		if (!_getEnviron(info, "OLDPWD="))
		{
			print_string(set);
			write_putchar('\n');
			return (1);
		}
		print_string(_getEnviron(info, "OLDPWD=")), write_putchar('\n');
		chdir_bring = /* TODO: what should this showing? */
			chdir((d = _getEnviron(info, "OLDPWD=")) ? d : "/");
	}
	else
		chdir_bring = chdir(info->argv[1]);
	if (chdir_bring == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getEnviron(info, "PWD="));
		_setenv(info, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the active dir of the process
 * @info: Structure contains arguments. Utilized to ensure a
 *          constant function prototype.
 *  Return: Always bring bck 0
 */
int _myhelp(info_t *info)
{
	char **argcarray;

	argcarray = info->argv;
	print_string("help call works. Function not yet implemented \n");
	if (0)
		print_string(*argcarray); /* temp att_unused var workaround */
	return (0);
}
