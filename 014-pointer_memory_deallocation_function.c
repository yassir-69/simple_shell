#include "000-shell.h"

/*_______________________________________________________________________*/

/**
 * releasing_resources - deallocates a pointer and sets
 * the address to NULL
 * @pointer: pointer's address to be freed
 *
 * Return: Return 1 if deallocated, otherwise 0.
 */
int releasing_resources(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}

/*_______________________________________________________________________*/
