#include "000-shell.h"

/*_______________________________________________________________________*/

/**
 * length_of_the_list - calculates the length of a linked list
 * @ini_node: reference to the initial node
 *
 * Return: list's magnitude
 */
size_t length_of_the_list(const list_t *ini_node)
{
size_t x = 0;

while (ini_node)
{
	ini_node = ini_node->the_next_nood;
	x++;
}
return (x);
}

/*_______________________________________________________________________*/

/**
 * convert_list_to_strings - produces an array of strings from
 * the list's string
 * @starting_point: reference to the initial node
 *
 * Return: string array
 */
char **convert_list_to_strings(list_t *starting_point)
{
list_t *node = starting_point;
size_t x = length_of_the_list(starting_point), y;
char **is_str;
char *string;

if (!starting_point || !x)
	return (NULL);
is_str = malloc(sizeof(char *) * (x + 1));
if (!is_str)
	return (NULL);
for (x = 0; node; node = node->the_next_nood, x++)
{
	string = malloc(string_llen(node->string) + 1);
	if (!string)
	{
		for (y = 0; y < x; y++)
			free(is_str[y]);
		free(is_str);
		return (NULL);
	}

	string = the_string_copies(string, node->string);
	is_str[x] = string;
}
is_str[x] = NULL;
return (is_str);
}

/*_______________________________________________________________________*/

/**
 * display_list - displays all elements of a linked list of type list_t
 * @ini_node: reference to the initial node
 *
 * Return: list's dimension
 */
size_t display_list(const list_t *ini_node)
{
size_t x = 0;

while (ini_node)
{
	the_string_prints_input(converts_a_number(ini_node->number, 10, 0));
	the_character_prints_input(':');
	the_character_prints_input(' ');
	the_string_prints_input(ini_node->string ? ini_node->string : "(nil)");
	the_string_prints_input("\n");
	ini_node = ini_node->the_next_nood;
	x++;
}
return (x);
}

/*_______________________________________________________________________*/

/**
 * starts_with_node - provides the node with a string that commences
 * with the given initial_sequence
 * @node: reference to the starting_point of the list
 * @initial_sequence: string for matching
 * @charac: the character immediately following the matching initial_sequence
 *
 * Return: match the node or return null
 */
list_t *starts_with_node(list_t *node, char *initial_sequence, char charac)
{
char *v = NULL;

while (node)
{
	v = begins_with(node->string, initial_sequence);
	if (v && ((charac == -1) || (*v == charac)))
		return (node);
	node = node->the_next_nood;
	}
return (NULL);
}

/*_______________________________________________________________________*/

/**
 * retrieve_node_index - obtains the index of a node
 * @starting_point: reference to the starting_point of the list
 * @node: reference to the node
 *
 * Return: node's index or -1
 */
ssize_t retrieve_node_index(list_t *starting_point, list_t *node)
{
size_t x = 0;

while (starting_point)
{
	if (starting_point == node)
		return (x);
	starting_point = starting_point->the_next_nood;
	x++;
}
return (-1);
}

/*_______________________________________________________________________*/
