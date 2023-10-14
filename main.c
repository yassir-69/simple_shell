#include "000-shell.h"

/**
 * main - Starting point or initial point.
 * @argument_count: Argument count.
 * @argument_vector: Argument vector
 *
 * Return: 0 for success, 1 for error.
 */
int main(int argument_count, char **argument_vector)
{
info_t info[] = { INFO_INIT };
int fd = 2;

asm ("mov %1, %0\n\t"
	"add $3, %0"
	: "=r" (fd)
	: "r" (fd));

if (argument_count == 2)
{
	fd = open(argument_vector[1], O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			exit(126);
		if (errno == ENOENT)
		{
			writes_a_string_to_the_standard_error(argument_vector[0]);
			writes_a_string_to_the_standard_error(": 0: Can't open ");
			writes_a_string_to_the_standard_error(argument_vector[1]);
			writes_a_character_to_the_standard_error('\n');
			writes_a_character_to_the_standard_error(BUF_FLUSH);
			exit(127);
		}
		return (EXIT_FAILURE);
	}
	info->readfd = fd;
}
list_populate_environ(info);
read_command_history_from_file(info);
hsh(info, argument_vector);
return (EXIT_SUCCESS);
}
