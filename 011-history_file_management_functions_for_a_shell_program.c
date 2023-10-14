#include "000-shell.h"

/*_______________________________________________________________________*/

/**
 * the_history_file - Retrieve the file path for the history file.
 * @info: Parameter structure containing potential arguments, used to
 * maintain a constant function prototype.
 *
 * Return: Dynamically allocated string containing the history file.
 */
char *the_history_file(info_t *info)
{
char *buffer, *directory;

directory = the_get_environ(info, "HOME=");
if (!directory)
	return (NULL);
buffer = malloc(sizeof(char) * (string_llen(directory) + string_llen(HIST_FILE) + 2));
if (!buffer)
		return (NULL);
buffer[0] = 0;
the_string_copies(buffer, directory);
string_ccat(buffer, "/");
string_ccat(buffer, HIST_FILE);
return (buffer);
}

/*_______________________________________________________________________*/

/**
 * write_the_history_file - Creates a new file or appends to an existing one.
 * @info: Parameter structure containing potential arguments, used to
 * maintain a constant function prototype.
 *
 * Return: Returns 1 on success, otherwise -1.
 */
int write_the_history_file(info_t *info)
{
ssize_t file_descriptor;
char *is_filename = the_history_file(info);
list_t *node = NULL;

if (!is_filename)
	return (-1);

file_descriptor = open(is_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(is_filename);
if (file_descriptor == -1)
	return (-1);
for (node = info->history; node; node = node->the_next_nood)
{
	writes_a_string_to_a_file_descriptor(node->string, file_descriptor);
	writes_to_a_file_descriptor('\n', file_descriptor);
}
writes_to_a_file_descriptor(BUF_FLUSH, file_descriptor);
close(file_descriptor);
return (1);
}

/*_______________________________________________________________________*/

/**
 * read_command_history_from_file - the Reads history from a file.
 * @info: Parameter structure containing potential arguments, used to
 * maintain a constant function prototype.
 *
 * Return: Returns histcount on success, 0 otherwise.
 */
int read_command_history_from_file(info_t *info)
{
int x, last = 0, linecount = 0;
ssize_t file_descriptor, rdlen, file_size = 0;
struct stat st;
char *buffer = NULL, *is_filename = the_history_file(info);

if (!is_filename)
	return (0);

file_descriptor = open(is_filename, O_RDONLY);
free(is_filename);
if (file_descriptor == -1)
	return (0);
if (!fstat(file_descriptor, &st))
	file_size = st.st_size;
if (file_size < 2)
	return (0);
buffer = malloc(sizeof(char) * (file_size + 1));
if (!buffer)
	return (0);
rdlen = read(file_descriptor, buffer, file_size);
buffer[file_size] = 0;
if (rdlen <= 0)
	return (free(buffer), 0);
close(file_descriptor);
for (x = 0; x < file_size; x++)
	if (buffer[x] == '\n')
	{
	buffer[x] = 0;
	create_list_from_command_history(info, buffer + last, linecount++);
	last = x + 1;
	}
if (last != x)
	create_list_from_command_history(info, buffer + last, linecount++);
free(buffer);
info->histcount = linecount;
while (info->histcount-- >= HIST_MAX)
	deletes_node_at_specified_index(&(info->history), 0);
update_line_numbers_command_history(info);
return (info->histcount);
}

/*_______________________________________________________________________*/

/**
 * create_list_from_command_history - Adds an entry to a linked
 * list containing history.
 * @info: A structure that holds possible arguments, employed to maintain
 * a consistent function prototype.
 * @buffer: A temporary storage area or region used for holding data.
 * @linecount: The history line count, also known as `histcount`, refers to
 * the number of entries or lines in the command history.
 *
 * Return: This function always returns the value 0.
 */
int create_list_from_command_history(info_t *info, char *buffer, int linecount)
{
list_t *node = NULL;

if (info->history)
	node = info->history;
appends_a_new_node_at_end(&node, buffer, linecount);

if (!info->history)
	info->history = node;
return (0);
}

/*_______________________________________________________________________*/

/**
 * update_line_numbers_command_history - This function adjusts the numbering
 * of entries in the history linked list.
 * list after changes
 * @info: This function involves a structure that holds potential arguments,
 * maintaining a consistent function prototype.
 *
 * Return: The updated histcount value.
 */
int update_line_numbers_command_history(info_t *info)
{
list_t *node = info->history;
int x = 0;

while (node)
{
	node->number = x++;
	node = node->the_next_nood;
}
return (info->histcount = x);
}

/*_______________________________________________________________________*/
