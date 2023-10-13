#include "000-shell.h"

/*______________________________________________________________________*/

/**
 * in_a_user_interactive_mode - Returns true if the shell is operating
 * in interactive mode.
 * @info: Structure representing an address.
 *
 * Return: 1 if currently in a user in_a_user_interactive_mode,
 * 0 otherwise.
 */
int in_a_user_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/*______________________________________________________________________*/

/**
 * is_a_delimiter - Examines whether the character functions
 * as a delimiter.
 * @charac: The character to be examined.
 * @delimiter: The string containing delimiters.
 * Return: 1 for true, 0 for false.
 */
int is_a_delimiter(char charac, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == charac)
			return (1);
	return (0);
}

/*______________________________________________________________________*/

/**
 * alphabetic_char - Examines if the character is an alphabetic character.
 * @charac: The character to be input.
 * Return: 1 if 'charac' is an alphabetic character, 0 otherwise.
 */

int alphabetic_char(int charac)
{
	if ((charac >= 'a' && charac <= 'z') || (charac >= 'A' && charac <= 'Z'))
		return (1);
	else
		return (0);
}

/*______________________________________________________________________*/

/**
 * integer_string - Transforms a string into an integer.
 * @int_string: The string undergoing conversion.
 * Return: Returns 0 if there are no numbers in the string, otherwise
 * provides the converted number.
 */

int integer_string(char *int_string)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  int_string[i] != '\0' && flag != 2; i++)
	{
		if (int_string[i] == '-')
			sign *= -1;

		if (int_string[i] >= '0' && int_string[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (int_string[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/*______________________________________________________________________*/
