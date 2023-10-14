#include "000-shell.h"

/*_______________________________________________________________________*/

/**
 * the_string_copies - Duplicates the content of a string. or copies a string
 * @_destination: The target or receiving location. or destination
 * @_source: The origin or the provider of data.or source
 *
 * Return: Pointer indicating the location of the destination.
 */
char *the_string_copies(char *_destination, char *_source)
{
int x = 0;

if (_destination == _source || _source == 0)
	return (_destination);
while (_source[x])
{
	_destination[x] = _source[x];
	x++;
}
_destination[x] = 0;
return (_destination);
}

/*_______________________________________________________________________*/

/**
 * the_string_duplicates - Creates a copy of a string.
 * @string: The text to replicate or create a copy of.
 *
 * Return: Pointer indicating the location of the replicated string.
 */
char *the_string_duplicates(const char *string)
{
int extent = 0;
char *retur;

if (string == NULL)
	return (NULL);
while (*string++)
	extent++;
retur = malloc(sizeof(char) * (extent + 1));
if (!retur)
	return (NULL);
for (extent++; extent--;)
	retur[extent] = *--string;
return (retur);
}

/*_______________________________________________________________________*/

/**
 *the_string_prints_input - Outputs or displays a given string.
 *@string: The text intended for output or display.
 *
 * Return: Nothing - absence or lack of anything
 */
void the_string_prints_input(char *string)
{
int x = 0;

if (!string)
	return;
while (string[x] != '\0')
{
	the_character_prints_input(string[x]);
	x++;
}
}

/*_______________________________________________________________________*/

/**
 * the_character_prints_input - Outputs the character 'charac' to
 * the standard output.
 * @charac: The character intended for printing or output.
 *
 * Return: Returns 1 if successful.
 * If there is an error, it returns -1, and the appropriate error code
 * is set in the errno variable.
 */
int the_character_prints_input(char charac)
{
static int x;
static char buf[WRITE_BUF_SIZE];

if (charac == BUF_FLUSH || x >= WRITE_BUF_SIZE)
{
	write(1, buf, x);
	x = 0;
}
if (charac != BUF_FLUSH)
	buf[x++] = charac;
return (1);
}

/*_______________________________________________________________________*/
