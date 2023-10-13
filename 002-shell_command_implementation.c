#include "000-shell.h"

/*______________________________________________________________________*/

/**
 * exit_shell - terminates the shell
 * @info: A structure holding possible arguments,
 * employed to uphold a consistent function prototype.
 * Return: Exits with a specified exit status
 * (0) if info.argv[0] is not "exit"
 */
int exit_shell(info_t *info)
{
int exit_condition;

if (info->argv[1])  /* If there is "exit" argument. */
{
	exit_condition = handling_errors(info->argv[1]);
	if (exit_condition == -1)
	{
		info->status = 2;
		displays_an_error(info, "Illegal number: ");
		writes_a_string_to_the_standard_error(info->argv[1]);
		writes_a_character_to_the_standard_error('\n');
		return (1);
	}
	info->err_num = handling_errors(info->argv[1]);
	return (-2);
}
info->err_num = -1;
return (-2);
}

/*______________________________________________________________________*/

/**
 * cd_shell - Modifies the current directory of the process.
 * @info: A structure that holds possible arguments, employed
 * to ensure a consistent function prototype..
 * Return: Constantly 0.
 */
int cd_shell(info_t *info)
{
char *structure, *is_dir, buffer[1024];
int return_val;

structure = getcwd(buffer, 1024);
if (!structure)
	the_string_prints_input("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
	is_dir = the_get_environ(info, "HOME=");
	if (!is_dir)
		(return_val = /* TODO: What is the expected value for this? */
			chdir((is_dir = the_get_environ(info, "PWD=")) ? is_dir : "/"));
	else
		(return_val = chdir(is_dir));
}
else if (string_ccmp(info->argv[1], "-") == 0)
{
	if (!the_get_environ(info, "OLDPWD="))
	{
		the_string_prints_input(structure);
		the_character_prints_input('\n');
		return (1);
	}
the_string_prints_input(the_get_environ(info, "OLDPWD=")), the_character_prints_input('\n');
(return_val = /* TODO: What is the expected value for this? */
	chdir((is_dir = the_get_environ(info, "OLDPWD=")) ? is_dir : "/"));
}   else
		(return_val = chdir(info->argv[1]));
if (return_val == -1)
{
	displays_an_error(info, "can't cd to ");
	writes_a_string_to_the_standard_error(info->argv[1]),
	writes_a_character_to_the_standard_error('\n');
}   else
{
set_an_environment_variable(info, "OLDPWD", the_get_environ(info, "PWD="));
set_an_environment_variable(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/*_______________________________________________________________________*/

/**
 * the_help - Modifies the process'structure current directory.
 * @info: A structure holding potential arguments, employed to
 * preserve a consistent function prototype.
 *  Return: Constantly 0.
 */
int the_help(info_t *info)
{
char **arrye_arguments;

arrye_arguments = info->argv;
the_string_prints_input("help call works. Function not yet implemented \n");
if (0)
	the_string_prints_input(*arrye_arguments); /* Temporary attribute_unused workaround. */
return (0);
}

/*_______________________________________________________________________*/

