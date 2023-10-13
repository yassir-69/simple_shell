#include "000-shell.h"

/**
 * writes_a_string_to_the_standard_error - Displays an input string.
 * @string: The string intended for printing.
 *
 * Return: No action required.
 */
void writes_a_string_to_the_standard_error(char *string)
{
	int x = 0;

	if (!string)
		return;
	while (string[x] != '\0')
	{
		writes_a_character_to_the_standard_error(string[x]);
		x++;
	}
}

/*______________________________________________________________________*/

/**
 * writes_a_character_to_the_standard_error - Outputs the character 'c'
 * to the standard error stream.
 * @c: The character to be printed.
 *
 * Return: Returns 1 on success.
 * Returns -1 on error, with the error code stored in the "errno" variable.
 */
int writes_a_character_to_the_standard_error(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

/*______________________________________________________________________*/

/**
 * writes_to_a_file_descriptor - Writes the character 'c' to the specified
 * file descriptor.
 * @c: The character intended for printing.
 * @fd: The file descriptor to which the character is written.
 *
 * Return: Returns 1 on success..
 * On error, -1 is returned, and errno is set appropriately.
 */
int writes_to_a_file_descriptor(char c, int fd)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fd, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

/*______________________________________________________________________*/

/**
 *writes_a_string_to_a_file_descriptor - Displays a given input string.
 * @string: The string intended for printing.
 * @fd: The file descriptor to which the character is written.
 *
 * Return: The count of characters that were printed.
 */
int writes_a_string_to_a_file_descriptor(char *string, int fd)
{
	int x = 0;

	if (!string)
		return (0);
	while (*string)
	{
		x += writes_to_a_file_descriptor(*string++, fd);
	}
	return (x);
}

/*______________________________________________________________________*/

