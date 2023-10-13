#include "000-shell.h"

/*______________________________________________________________________*/

/**
 * reset_fields_of_information_structure - Initialize the `info_t` structure.
 * @info: Address of the structure.
 */
void reset_fields_of_information_structure(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}

/*______________________________________________________________________*/

/**
 * set_fields_of_information_structure - Initializes the structure of type
 * "info_t."
 * @info: Address of the structure.
 * @arguments_vector: Vector containing command-line arguments.
 */
void set_fields_of_information_structure(info_t *info, char **arguments_vector)
{
int x = 0;

info->fname = arguments_vector[0];
if (info->arg)
{
	info->argv = string_into_words(info->arg, " \t");
	if (!info->argv)
	{

		info->argv = malloc(sizeof(char *) * 2);
		if (info->argv)
		{
			info->argv[0] = the_string_duplicates(info->arg);
			info->argv[1] = NULL;
		}
	}
	for (x = 0; info->argv && info->argv[x]; x++)
		;
	info->argc = x;

	substitute_alias(info);
	substitute_vars(info);
}
}

/*______________________________________________________________________*/

/**
 * Free_memory_used_information_structure - Frees the fields of the "info_t"
 * structure.
 * @info: Address of the structure.
 * @all_fields: Returns true if all fields are freed.
 */
void Free_memory_used_information_structure(info_t *info, int all_fields)
{
f_free_string(info->argv);
info->argv = NULL;
info->path = NULL;
if (all_fields)
{
	if (!info->cmd_buf)
		free(info->arg);
	if (info->env)
		frees_memory_allocated_for_linked_list(&(info->env));
	if (info->history)
		frees_memory_allocated_for_linked_list(&(info->history));
	if (info->alias)
		frees_memory_allocated_for_linked_list(&(info->alias));
	f_free_string(info->environ);
		info->environ = NULL;
	releasing_resources((void **)info->cmd_buf);
	if (info->readfd > 2)
		close(info->readfd);
	the_character_prints_input(BUF_FLUSH);
}
}

/*______________________________________________________________________*/

