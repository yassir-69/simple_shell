#include "000-shell.h"

/*_______________________________________________________________________*/

/**
 * hsh - primary shell loop or main shell loop.
 * @info: the argument and result structure
 * @argumentv: the parameter array in main()
 *
 * Return: 0 for success, 1 for failure, or the error code
 */
int hsh(info_t *info, char **argumentv)
{
	ssize_t i = 0;
	int return_from_builtin = 0;

	while (i != -1 && return_from_builtin != -2)
	{
		reset_fields_of_information_structure(info);
		if (in_a_user_interactive_mode(info))
			the_string_prints_input("$ ");
		writes_a_character_to_the_standard_error(BUF_FLUSH);
		i = receive_input(info);
		if (i != -1)
		{
			set_fields_of_information_structure(info, argumentv);
			return_from_builtin = locate_builtin(info);
			if (return_from_builtin == -1)
				locate_command(info);
		}
		else if (in_a_user_interactive_mode(info))
			the_character_prints_input('\n');
		Free_memory_used_information_structure(info, 0);
	}
	write_the_history_file(info);
	Free_memory_used_information_structure(info, 1);
	if (!in_a_user_interactive_mode(info) && info->status)
		exit(info->status);
	if (return_from_builtin == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (return_from_builtin);
}

/*_______________________________________________________________________*/

/**
 * locate_builtin - locates a built-in command or finds builtin command
 * @info: the argument and result structure
 *
 * Return: 
 * -1 if the built-in command is not found,
 * 0 if the built-in command is executed successfully,
 * 1 if the built-in command is found but not successful,
 * -2 if the built-in command signals an exit()
 */
int locate_builtin(info_t *info)
{
	int x, return_in_builtin = -1;
	builtin_table builtintbl[] = {
		{"exit", exit_shell},
		{"env", the_environ},
		{"help", the_help},
		{"history", display_history},
		{"setenv", the_set_environ},
		{"unsetenv", unset_environ},
		{"cd", cd_shell},
		{"alias", the_alias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].is_type; x++)
		if (string_ccmp(info->argv[0], builtintbl[x].is_type) == 0)
		{
			info->line_count++;
			return_in_builtin = builtintbl[x].function(info);
			break;
		}
	return (return_in_builtin);
}

/*_______________________________________________________________________*/

/**
 * locate_command - locates a command in the PATH variable
 * @info: the argument and result structure
 *
 * Return: empty or null or void
 */
void locate_command(info_t *info)
{
	char *path = NULL;
	int x, l;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0, l = 0; info->arg[x]; x++)
		if (!is_a_delimiter(info->arg[x], " \t\n"))
			l++;
	if (!l)
		return;

	path = locate_route(info, the_get_environ(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((in_a_user_interactive_mode(info) || the_get_environ(info, "PATH=")
			|| info->argv[0][0] == '/') && cmd_check(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			displays_an_error(info, "not found\n");
		}
	}
}

/*_______________________________________________________________________*/

/**
 * fork_command - forks a an exec thread to run cmd
 * @info: the argument and result structure
 *
 * Return: empty or null or void
 */
void fork_command(info_t *info)
{
	pid_t child_process_id;

	child_process_id = fork();
	if (child_process_id == -1)
	{
		/* TODO: Create an error function */
		perror("Error:");
		return;
	}
	if (child_process_id == 0)
	{
		if (execve(info->path, info->argv, retrieve_environment(info)) == -1)
		{
			Free_memory_used_information_structure(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: Create an error function */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				displays_an_error(info, "Permission denied\n");
		}
	}
}

/*_______________________________________________________________________*/
