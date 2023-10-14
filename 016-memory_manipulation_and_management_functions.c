#include "000-shell.h"

/*_______________________________________________________________________*/

/**
 * *underscore_memset - populates memory with a uniform byte
 * @ref_mem: reference to the memory region
 * @byte_used: byte used to populate *ref_mem
 * @byte_filed: quantity of bytes to fill or amount of bytes to be filled
 * Return: Return: (ref_mem) a reference to the memory space ref_mem
 */
char *underscore_memset(char *ref_mem, char byte_used, unsigned int byte_filed)
{
unsigned int x;

for (x = 0; x < byte_filed; x++)
	ref_mem[x] = byte_used;
return (ref_mem);
}

/*_______________________________________________________________________*/

/**
 * f_free_string - deallocates an array of strings
 * @string_of_string: collection of strings or string of strings
 */
void f_free_string(char **string_of_string)
{
char **a = string_of_string;

if (!string_of_string)
	return;
while (*string_of_string)
	free(*string_of_string++);
free(a);
}

/*_______________________________________________________________________*/

/**
 * underscore_realloc - adjusts the size of a memory block
 * @rpl: reference to the previously allocated memory block
 * @sizold: size in bytes of the preceding block
 * @sizenew: size in bytes of the newly allocated block
 *
 * Return: reference to the old block, you know what I mean.
 */
void *underscore_realloc(void *rpl, unsigned int sizold, unsigned int sizenew)
{
char *q;

if (!rpl)
	return (malloc(sizenew));
if (!sizenew)
	return (free(rpl), NULL);
if (sizenew == sizold)
	return (rpl);

q = malloc(sizenew);
if (!q)
	return (NULL);

sizold = sizold < sizenew ? sizold : sizenew;
while (sizold--)
	q[sizold] = ((char *)rpl)[sizold];
free(rpl);
return (q);
}

/*_______________________________________________________________________*/
