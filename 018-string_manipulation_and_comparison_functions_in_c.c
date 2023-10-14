#include "000-shell.h"

/*_______________________________________________________________________*/

/**
 * string_llen -provides the size of a string or returns length of a string
 * @_str: the string to determine its length
 *
 * Return: integer size of the string
 */
int string_llen(char *_str)
{
int x = 0;

if (!_str)
	return (0);

while (*_str++)
	x++;
return (x);
}

/*_______________________________________________________________________*/

/**
 * string_ccmp - The process of lexicographic comparison between two strings
 * is performed by the "conducts" operation..
 * @first_str:  strang first
 * @second_str:  strang second
 *
 * Return: Returns a negative value if first_str is less than second_str,
 * a positive value
 * if first_str is greater than second_str, and zero if first_str is equal
 * to second_str.
 */
int string_ccmp(char *first_str, char *second_str)
{
while (*first_str && *second_str)
{
	if (*first_str != *second_str)
		return (*first_str - *second_str);
	first_str++;
	second_str++;
}
if (*first_str == *second_str)
	return (0);
else
	return (*first_str < *second_str ? -1 : 1);
}

/*_______________________________________________________________________*/

/**
 * begins_with - Verifies whether the string "is_needle" begins with
 * the content of the string "is_haystack."
 * @is_haystack: The string to be searched.
 * @is_needle: The portion of text to locate. or the substring to find
 *
 * Return: The memory location of the next character in the haystack
 * or NULL if not found.
 */
char *begins_with(const char *is_haystack, const char *is_needle)
{
while (*is_needle)
	if (*is_needle++ != *is_haystack++)
		return (NULL);
return ((char *)is_haystack);
}

/*_______________________________________________________________________*/

/**
 * string_ccat - Combines or joins two strings.
 * @destination: The buffer where the data will be copied or stored.
 * or the destination buffer
 * @source: The buffer from which data will be copied or retrieved. or
 * the source buffer
 *
 * Return: Pointer to the destination buffer, indicating the memory location
 * where data will be stored.
 */
char *string_ccat(char *destination, char *source)
{
	char *retur = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (retur);
}

/*_______________________________________________________________________*/
