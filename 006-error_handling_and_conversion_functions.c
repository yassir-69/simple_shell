#include "000-shell.h"

/*______________________________________________________________________*/

/**
 * handling_errors - Changes a string into an integer.
 * @str: The string intended for conversion.
 * Return: Returns 0 if there are no numbers in the string,
 * and the converted number otherwise. Returns -1 on error.
 */
int handling_errors(char *str)
{
int x = 0;
unsigned long int resulting_value = 0;

if (*str == '+')
	str++;  /* TODO: What causes the main function to return 255? */
for (x = 0;  str[x] != '\0'; x++)
{
	if (str[x] >= '0' && str[x] <= '9')
	{
		resulting_value *= 10;
		resulting_value += (str[x] - '0');
		if (resulting_value > INT_MAX)
			return (-1);
	}
	else
		return (-1);
}
return (resulting_value);
}

/*______________________________________________________________________*/

/**
 * displays_an_error - Displays an error message.
 * @info: The information structure used for both parameters and
 * return values.
 * @estr: A string representing the specified error type.
 * Return: Returns 0 if there are no numbers in the string,
 * and the converted number otherwise. Returns -1 on error.
 */
void displays_an_error(info_t *info, char *estr)
{
writes_a_string_to_the_standard_error(info->fname);
writes_a_string_to_the_standard_error(": ");
print_decimal(info->line_count, STDERR_FILENO);
writes_a_string_to_the_standard_error(": ");
writes_a_string_to_the_standard_error(info->argv[0]);
writes_a_string_to_the_standard_error(": ");
writes_a_string_to_the_standard_error(estr);
}

/*______________________________________________________________________*/

/**
 * print_decimal - The function displays a decimal (integer) number
 * in base 10.
 * @input: The provided input.
 * @fd: The file descriptor to which the output is written.
 *
 * Return: Count of printed characters.
 */
int print_decimal(int input, int fd)
{
int (*__putchar)(char) = the_character_prints_input;
int x, is_count = 0;
unsigned int _abs, current_state;

if (fd == STDERR_FILENO)
	__putchar = writes_a_character_to_the_standard_error;
if (input < 0)
{
	_abs = -input;
	__putchar('-');
	is_count++;
}
else
	_abs = input;
current_state = _abs;
for (x = 1000000000; x > 1; x /= 10)
{
	if (_abs / x)
	{
		__putchar('0' + current_state / x);
		is_count++;
	}
	current_state %= x;
}
__putchar('0' + current_state);
is_count++;

return (is_count);
}

/*______________________________________________________________________*/

/**
 * converts_a_number - Conversion function, similar to itoa.
 * @num: The numerical value.
 * @base: The numerical base.
 * @flags_used: Flags used as arguments.
 *
 * Return: Returns a string.
 */
char *converts_a_number(long int num, int base, int flags_used)
{
static char *array;
static char buffer[50];
char the_sign = 0;
char *pointer;
unsigned long m = num;

if (!(flags_used & CONVERT_UNSIGNED) && num < 0)
{
	m = -num;
	the_sign = '-';

}
array = flags_used & CONVERT_LOWERCASE ?
"0123456789abcdef" : "0123456789ABCDEF";
pointer = &buffer[49];
*pointer = '\0';

do	{
	*--pointer = array[m % base];
	m /= base;
} while (m != 0);

if (the_sign)
	*--pointer = the_sign;
return (pointer);
}

/*______________________________________________________________________*/

/**
 * eliminates_comments - The function substitutes the first occurrence of
 * '#' with '\0' (null character).
 * @buf: The memory address of the string to be modified.
 *
 * Return: Consistently 0.;
 */
void eliminates_comments(char *buf)
{
	int x;

for (x = 0; buf[x] != '\0'; x++)
	if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
	{
		buf[x] = '\0';
		break;
	}
}

/*______________________________________________________________________*/

