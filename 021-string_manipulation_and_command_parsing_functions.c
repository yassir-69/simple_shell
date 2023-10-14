#include "000-shell.h"

/*_______________________________________________________________________*/

/**
 * chain_delimeter - Check whether the present character in the buffer
 * is a delimiter for a chain.
 * @info: Rewrite the structure of the parameter.
 * @buffer: The character buffer
 * @position: The memory location of the current position in the buffer.
 *
 * Return: 1 if it's a delimiter for a chain, 0 otherwise.
 */
int chain_delimeter(info_t *info, char *buffer, size_t *position)
{
size_t y = *position;

if (buffer[y] == '|' && buffer[y + 1] == '|')
{
	buffer[y] = 0;
	y++;
	info->cmd_buf_type = CMD_OR;
}
else if (buffer[y] == '&' && buffer[y + 1] == '&')
{
	buffer[y] = 0;
	y++;
	info->cmd_buf_type = CMD_AND;
}
else if (buffer[y] == ';') /* Identified the conclusion of this command. */
{
	buffer[y] = 0; /* Substitute the semicolon with null. */
	info->cmd_buf_type = CMD_CHAIN;
}
else
	return (0);
*position = y;
return (1);
}

/*_______________________________________________________________________*/

/**
 * check_chain_delimeter - Examines whether we should persist with chaining
 * according to the previous status.
 * @info: Rewrite the structure of the parameter.
 * @buffer: The character buffer
 * @position: The memory location of the current position in the buffer
 * @initial: Initial location in the buffer.
 * @length: length or Size of the buffer.
 *
 * Return: Voidn Empty or devoid.
 */
void check_chain_delimeter(info_t *info, char *buffer, size_t *position, size_t initial, size_t length)
{
size_t y = *position;

if (info->cmd_buf_type == CMD_AND)
{
	if (info->status)
	{
		buffer[initial] = 0;
		y = length;
	}
}
if (info->cmd_buf_type == CMD_OR)
{
	if (!info->status)
	{
		buffer[initial] = 0;
		y = length;
	}
}

*position = y;
}

/*_______________________________________________________________________*/

/**
 * substitute_alias - Substitutes aliases within the tokenized string.
 * @info: Rewrite the structure of the parameter.
 *
 * Return: 1 if substitution occurred, 0 otherwise.
 */
int substitute_alias(info_t *info)
{
int x;
list_t *node;
char *position;

for (x = 0; x < 10; x++)
{
	node = starts_with_node(info->alias, info->argv[0], '=');
	if (!node)
		return (0);
	free(info->argv[0]);
	position = string_charac(node->string, '=');
	if (!position)
		return (0);
	position = the_string_duplicates(position + 1);
	if (!position)
		return (0);
	info->argv[0] = position;
}
return (1);
}

/*_______________________________________________________________________*/

/**
 * substitute_vars - Substitutes variables within the tokenized string.
 * @info: Rewrite the structure of the parameter.
 *
 * Return: 1 if substitution occurred, 0 otherwise.
 */
int substitute_vars(info_t *info)
{
int x = 0;
list_t *node;

for (x = 0; info->argv[x]; x++)
{
	if (info->argv[x][0] != '$' || !info->argv[x][1])
		continue;

	if (!string_ccmp(info->argv[x], "$?"))
	{
		substitute_string(&(info->argv[x]),
			the_string_duplicates(converts_a_number(info->status, 10, 0)));
		continue;
	}
	if (!string_ccmp(info->argv[x], "$$"))
	{
		substitute_string(&(info->argv[x]),
			the_string_duplicates(converts_a_number(getpid(), 10, 0)));
		continue;
	}
	node = starts_with_node(info->env, &info->argv[x][1], '=');
	if (node)
	{
		substitute_string(&(info->argv[x]),
			the_string_duplicates(string_charac(node->string, '=') + 1));
		continue;
	}
	substitute_string(&info->argv[x], the_string_duplicates(""));

}
return (0);
}
 
/*_______________________________________________________________________*/

/**
 * substitute_string - Substitutes the string.
 * @previous: Memory location of the previous string.
 * @fresh: Fresh string or updated string.
 *
 * Return: 1 if substitution occurred, 0 otherwise.
 */
int substitute_string(char **previous, char *fresh)
{
free(*previous);
*previous = fresh;
return (1);
}

/*_______________________________________________________________________*/
