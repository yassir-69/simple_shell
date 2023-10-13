#include "000-shell.h"

/*______________________________________________________________________*/

/**
 * retrieve_environment - Returns a string array copy of the environment.
 * @info: A structure that holds potential arguments, ensuring a consistent
 * function prototype.
 * Return: Constantly 0.
 */
char **retrieve_environment(info_t *info)
{
if (!info->environ || info->env_changed)
{
	info->environ = convert_list_to_strings(info->env);
	info->env_changed = 0;
}

return (info->environ);
}

/*______________________________________________________________________*/

/**
 * unset_an_environment_variable - Delete an environment variable.
 * @info: A structure that holds potential arguments, maintaining
 * a constant function prototype.
 * Returns 1 upon successful deletion, 0 otherwise.
 * @variabl: The string representing the environment variable property.
 */
int unset_an_environment_variable(info_t *info, char *variabl)
{
list_t *node = info->env;
size_t x = 0;
char *h;

if (!node || !variabl)
	return (0);

while (node)
{
	h = begins_with(node->string, variabl);
	if (h && *h == '=')
	{
		info->env_changed = deletes_node_at_specified_index(&(info->env), x);
		x = 0;
		node = info->env;
		continue;
	}
	node = node->the_next_nood;
	x++;
}
return (info->env_changed);
}

/*______________________________________________________________________*/

/**
 * set_an_environment_variable - Initialize a new environment variable
 * or modify an existing one.
 * @info: A structure that holds potential arguments, maintaining a
 * constant function prototype.
 * @variabl: The string representing the environment variable property.
 * @is_value: The string representing the value of the environment variable.
 *  Return: Constantly 0.
 */
int set_an_environment_variable(info_t *info, char *variabl, char *is_value)
{
char *buf = NULL;
list_t *node;
char *h;

if (!variabl || !is_value)
	return (0);

buf = malloc(string_llen(variabl) + string_llen(is_value) + 2);
if (!buf)
	return (1);
the_string_copies(buf, variabl);
string_ccat(buf, "=");
string_ccat(buf, is_value);
node = info->env;
while (node)
{
	h = begins_with(node->string, variabl);
	if (h && *h == '=')
	{
		free(node->string);
		node->string = buf;
		info->env_changed = 1;
		return (0);
	}
	node = node->the_next_nood;
}
appends_a_new_node_at_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}

/*______________________________________________________________________*/


