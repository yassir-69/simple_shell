#include "000-shell.h"

/*______________________________________________________________________*/

/**
 * display_history - Shows the history list, presenting each command
 * on a separate line along with line numbers, beginning from 0.
 * @info: A structure that holds potential arguments, utilized to uphold
 * a consistent function prototype.
 * Return: Consistently 0.
 */
int display_history(info_t *info)
{
display_list(info->history);
return (0);
}

/*______________________________________________________________________*/

/**
 * remove_alias - Assigns an alias to a string.
 * @info: Struct containing parameters.
 * @string: The alias in string form.
 *
 * Return: Returns 0 for success and 1 for error.
 */
int remove_alias(info_t *info, char *string)
{
char *param, charac;
int retur;

param = string_charac(string, '=');
if (!param)
	return (1);
charac = *param;
*param = 0;
retur = deletes_node_at_specified_index(&(info->alias),
retrieve_node_index(info->alias, starts_with_node(info->alias, string, -1)));
*param = charac;
return (retur);
}

/*______________________________________________________________________*/

/**
 * establish_alias - Assigns an alias to a string.
 * @info: Structure containing parameters.
 * @string: The alias represented as a string.
 *
 * Return: Returns 0 for success and 1 for error.
 */
int establish_alias(info_t *info, char *string)
{
char *param;

param = string_charac(string, '=');
if (!param)
	return (1);
if (!*++param)
	return (remove_alias(info, string));

remove_alias(info, string);
return (appends_a_new_node_at_end(&(info->alias), string, 0) == NULL);
}

/*______________________________________________________________________*/

/**
 * show_alias - Displays an alias string.
 * @node: The node associated with aliases.
 *
 * Return: Returns 0 for success and 1 for error.
 */
int show_alias(list_t *node)
{
char *param = NULL, *i = NULL;

if (node)
{
	param = string_charac(node->string, '=');
	for (i = node->string; i <= param; i++)
		the_character_prints_input(*i);
	the_character_prints_input('\'');
	the_string_prints_input(param + 1);
	the_string_prints_input("'\n");
	return (0);
}
return (1);
}

/*______________________________________________________________________*/

/**
 * the_alias - Imitates the behavior of the alias built-in
 * (refer to 'man alias').
 * @info: A structure that holds potential arguments, employed
 * to preserve a consistent function prototype.
 * Return: Consistently 0.
 */
int the_alias(info_t *info)
{
int imitates = 0;
char *param = NULL;
list_t *node = NULL;

if (info->argc == 1)
{
	node = info->alias;
	while (node)
	{
		show_alias(node);
		node = node->the_next_nood;
	}
	return (0);
}
for (imitates = 1; info->argv[imitates]; imitates++)
{
	param = string_charac(info->argv[imitates], '=');
	if (param)
		establish_alias(info, info->argv[imitates]);
	else
		show_alias(starts_with_node(info->alias, info->argv[imitates], '='));
}

return (0);
}

/*______________________________________________________________________*/

