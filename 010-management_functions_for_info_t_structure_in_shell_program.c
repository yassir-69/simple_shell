#include "000-shell.h"

/*_______________________________________________________________________*/

/**
 * input_buffer - buffers linked commands
 * @info: the structure containing parameters
 * @buffer: pointer to the buffer's address
 * @length: pointer to the variable storing the length
 *
 * Return: the number of bytes read
 */
ssize_t input_buffer(info_t *info, char **buffer, size_t *length)
{
ssize_t y = 0;
size_t len_pointer = 0;

if (!*length) /* If there is no remaining content in buffer, refill it. */
{
	/*bfree((void **)info->cmd_buf);*/
	free(*buffer);
	*buffer = NULL;
	signal(SIGINT, signal_interrupt_handler);
#if USE_GETLINE
	y = getline(buffer, &len_pointer, stdin);
#else
	y = is_get_line(info, buffer, &len_pointer);
#endif
	if (y > 0)
	{
		if ((*buffer)[y - 1] == '\n')
		{
			(*buffer)[y - 1] = '\0'; /* Remove the newline character at end. */
			y--;
		}
		info->linecount_flag = 1;
		eliminates_comments(*buffer);
		create_list_from_command_history(info, *buffer, info->histcount++);
		/* Check if the character ';' is present in the string, indicating
		a command chain. */
		{
			*length = y;
			info->cmd_buf = buffer;
		}
	}
	}
	return (y);
}

/*_______________________________________________________________________*/

/**
 * receive_input - Retrieves a line without the trailing newline character.
 * @info: the structure containing parameters
 *
 * Return: the number of bytes read
 */
ssize_t receive_input(info_t *info)
{
static char *buffer; /* The buffer used for ';' command chaining. */
static size_t x, z, length;
ssize_t y = 0;
char **buffer_p = &(info->arg), *p;

the_character_prints_input(BUF_FLUSH);
y = input_buffer(info, &buffer, &length);
if (y == -1) /* EOF */
	return (-1);
if (length)	/* Commands are still present in the command chain buffer. */
{
	z = x; /* Initialize a new iterator to current position in buffer. */
	p = buffer + x; /* Retrieve a pointer for the return value. */

	check_chain_delimeter(info, buffer, &z, x, length);
	while (z < length) /* Iterate until a semicolon or the end is reached. */
	{
		if (chain_delimeter(info, buffer, &z))
			break;
		z++;
	}

	x = z + 1; /* Increment the pointer past the null character. ';'' */
	if (x >= length) /* Reached the end of the buffer.? */
	{
		x = length = 0; /* Reset the position and length. */
		info->cmd_buf_type = CMD_NORM;
	}

	*buffer_p = p; /* Pass back a pointer to the current command position. */
	return (string_llen(p)); /* Return the length of the current command. */
}

*buffer_p = buffer; /* Otherwise,if it's not a comm chain, return buffer from`is_get_line()` */
return (y); /* Return the length of the buffer obtained from the `is_get_line()` . */
}

/*_______________________________________________________________________*/

/**
 * read_buffer - Reads data into a buffer.
 * @info: the structure containing parameters
 * @buffer: Data storage location.
 * @x: Extent of data.
 *
 * Return: y
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *x)
{
ssize_t y = 0;

if (*x)
	return (0);
y = read(info->readfd, buffer, READ_BUF_SIZE);
if (y >= 0)
	*x = y;
return (y);
}

/*_______________________________________________________________________*/

/**
 * is_get_line - Retrieves subsequent line of input from standard input (STDIN).
 * @info: the structure containing parameters
 * @prea: Refers to the memory location of a pointer that points to a buffer,
 * which can either be preallocated or set to NULL.
 * @is_length: Specifies size of a preallocated pointer buffer if it is not NULL.
 *
 * Return: v
 */
int is_get_line(info_t *info, char **prea, size_t *is_length)
{
static char buffer[READ_BUF_SIZE];
static size_t x, length;
size_t k;
ssize_t y = 0, v = 0;
char *p = NULL, *is_new_p = NULL, *c;

p = *prea;
if (p && is_length)
	v = *is_length;
if (x == length)
	x = length = 0;

y = read_buffer(info, buffer, &length);
if (y == -1 || (y == 0 && length == 0))
	return (-1);

c = string_charac(buffer + x, '\n');
k = c ? 1 + (unsigned int)(c - buffer) : length;
is_new_p = underscore_realloc(p, v, v ? v + k : k + 1);
if (!is_new_p) /* MALLOC FAILURE! */
	return (p ? free(p), -1 : -1);

if (v)
	string_cat(is_new_p, buffer + x, k - x);
else
	string_copies(is_new_p, buffer + x, k - x + 1);

v += k - x;
x = k;
p = is_new_p;

if (is_length)
	*is_length = v;
*prea = p;
return (v);
}

/*_______________________________________________________________________*/

/**
 * signal_interrupt_handler - Prevents the interruption of the execution
 * by the Ctrl-C signal
 * @sig_num: The identifier for the signal.
 *
 * Return: the void
 */
void signal_interrupt_handler(__attribute__((unused))int sig_num)
{
the_string_prints_input("\n");
the_string_prints_input("$ ");
the_character_prints_input(BUF_FLUSH);
}

/*_______________________________________________________________________*/

