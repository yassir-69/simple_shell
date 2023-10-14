#include "000-shell.h"

/*_______________________________________________________________________*/

/**
 * **string_into_words - Divides a string into individual words,
 * disregarding repeated delimiters.
 * @string: The given or provided string.
 * @delimit: The string used as a delimiter.
 * Return: Returns a pointer to an array of strings, or NULL in 
 * case of failure.
 */

char **string_into_words(char *string, char *delimit)
{
int x, y, k, u, words_number = 0;
char **v;

if (string == NULL || string[0] == 0)
	return (NULL);
if (!delimit)
	delimit = " ";
for (x = 0; string[x] != '\0'; x++)
if (!is_a_delimiter(string[x], delimit) && (is_a_delimiter(string[x + 1], delimit) || !string[x + 1]))
		words_number++;

if (words_number == 0)
	return (NULL);
v = malloc((1 + words_number) * sizeof(char *));
if (!v)
	return (NULL);
for (x = 0, y = 0; y < words_number; y++)
{
	while (is_a_delimiter(string[x], delimit))
		x++;
	k = 0;
	while (!is_a_delimiter(string[x + k], delimit) && string[x + k])
		k++;
	v[y] = malloc((k + 1) * sizeof(char));
	if (!v[y])
	{
		for (k = 0; k < y; k++)
			free(v[k]);
		free(v);
		return (NULL);
	}
	for (u = 0; u < k; u++)
		v[y][u] = string[x++];
	v[y][u] = 0;
}
v[y] = NULL;
return (v);
}

/*_______________________________________________________________________*/

/**
 * **splits_string_into_words - Divides a string into individual words.
 * @string: The given or provided string
 * @delimit: The string used as a delimiter
 * Return: Returns a pointer to an array of strings, or NULL in 
 * case of failure.
 */
char **splits_string_into_words(char *string, char delimit)
{
int x, y, k, u, words_number = 0;
char **v;

if (string == NULL || string[0] == 0)
	return (NULL);
for (x = 0; string[x] != '\0'; x++)
	if ((string[x] != delimit && string[x + 1] == delimit) ||
	(string[x] != delimit && !string[x + 1]) || string[x + 1] == delimit)
		words_number++;
if (words_number == 0)
	return (NULL);
v = malloc((1 + words_number) * sizeof(char *));
if (!v)
	return (NULL);
for (x = 0, y = 0; y < words_number; y++)
{
	while (string[x] == delimit && string[x] != delimit)
		x++;
	k = 0;
while (string[x + k] != delimit && string[x + k] && string[x + k] != delimit)
		k++;
	v[y] = malloc((k + 1) * sizeof(char));
	if (!v[y])
	{
		for (k = 0; k < y; k++)
			free(v[k]);
		free(v);
		return (NULL);
	}
	for (u = 0; u < k; u++)
		v[y][u] = string[x++];
	v[y][u] = 0;
}
v[y] = NULL;
return (v);
}

/*_______________________________________________________________________*/
