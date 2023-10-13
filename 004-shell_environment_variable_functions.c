#include "000-shell.h"

/*______________________________________________________________________*/

/**
 * the_environ - Displays the current environment.
 * @info: A structure holding possible arguments, employed to ensure
 * a consistent function prototype.
 * Return: Consistently 0.
 */
int the_environ(info_t *info)
{
	prints_list_strings(info->env);
	return (0);
}

/*______________________________________________________________________*/

/**
 * the_get_environ - Retrieves the value of an environment variable.
 * @info: A structure holding potential arguments, employed for
 * consistent function prototypes.
 * @environ_name: The name of an environment variable.
 *
 * Return: is value
 */
char *the_get_environ(info_t *info, const char *environ_name)
{
	list_t *node = info->env;
	char *prot;

	while (node)
	{
		prot = begins_with(node->string, environ_name);
		if (prot && *prot)
			return (prot);
		node = node->the_next_nood;
	}
	return (NULL);
}

/*______________________________________________________________________*/

/**
 * the_set_environ - Create a new environment variable or modify
 * an existing one.
 * @info: A structure holding potential arguments, employed
 * for consistent function prototypes.
 * Return: Consistently 0.
 */
int the_set_environ(info_t *info)
{
	if (info->argc != 3)
	{
	writes_a_string_to_the_standard_error("Incorrect number of arguements\n");
	return (1);
	}
	if (set_an_environment_variable(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/*______________________________________________________________________*/

/**
 * unset_environ - Delete an environment variable.
 * @info: A structure holding potential arguments, employed for
 * consistent function prototypes.
 *  Return: Consistently 0.
 */
int unset_environ(info_t *info)
{
	int x;

	if (info->argc == 1)
	{
	writes_a_string_to_the_standard_error("Too few arguements.\n");
	return (1);
	}
	for (x = 1; x <= info->argc; x++)
		unset_an_environment_variable(info, info->argv[x]);

	return (0);
}

/*______________________________________________________________________*/

/**
 * list_populate_environ - Fills the linked list for the environment.
 * @info: A structure holding potential arguments, employed for
 * consistent function prototypes.
 * Return: Consistently 0.
 */
int list_populate_environ(info_t *info)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		appends_a_new_node_at_end(&node, environ[x], 0);
	info->env = node;
	return (0);
}

/*______________________________________________________________________*/

