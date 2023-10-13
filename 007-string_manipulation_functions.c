#include "000-shell.h"

/*______________________________________________________________________*/

/**
 * *string_copies - Performs string copying.
 * @_dest: The target string for the copy operation.
 * @_src: The string from which the copy is made.
 * @m: The number of characters to be copied.
 * Returns the combined string.
 */
char *string_copies(char *_dest, char *_src, int m)
{
int x, y;
char *stri = _dest;

x = 0;
while (_src[x] != '\0' && x < m - 1)
{
	_dest[x] = _src[x];
	x++;
}
if (x < m)
{
	y = x;
	while (y < m)
	{
		_dest[y] = '\0';
		y++;
	}
}
return (stri);
}

/*______________________________________________________________________*/

/**
 **string_cat - Combines two strings.
 *@_dest: The initial string.
 *@_src: The second string.
 *@m: The maximum number of bytes to be used.
 *Return: The result of the concatenation.
 */
char *string_cat(char *_dest, char *_src, int m)
{
int x, y;
char *stri = _dest;

x = 0;
y = 0;
while (_dest[x] != '\0')
	x++;
while (_src[y] != '\0' && y < m)
{
	_dest[x] = _src[y];
	x++;
	y++;
}
if (y < m)
	_dest[x] = '\0';
return (stri);
}

/*______________________________________________________________________*/

/**
 **string_charac - Finds the position of a character in a string.
 *@stri: The string subject to parsing.
 *@charac: The character to search for.
 *Returns: a pointer to the memory area containing the string (s).
 */
char *string_charac(char *stri, char charac)
{
do {
	if (*stri == charac)
		return (stri);
} while (*stri++ != '\0');

return (NULL);
}

/*______________________________________________________________________*/

