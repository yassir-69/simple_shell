#include "000-shell.h"

/*_______________________________________________________________________*/

/**
 * inserts_new_node - Adds a node at the beginning of the linked list.
 * @head: Refers to the address of the pointer pointing to the head node.
 * @string: Refers to the string field of a node.
 * @number: Refers to the index of a node utilized in the history.
 *
 * Return: Refers to the size or number of elements in the list.
 */
list_t *inserts_new_node(list_t **head, const char *string, int number)
{
list_t *the_new_head;

if (!head)
	return (NULL);
the_new_head = malloc(sizeof(list_t));
if (!the_new_head)
	return (NULL);
underscore_memset((void *)the_new_head, 0, sizeof(list_t));
the_new_head->number = number;
if (string)
{
	the_new_head->string = the_string_duplicates(string);
	if (!the_new_head->string)
	{
		free(the_new_head);
		return (NULL);
	}
}
the_new_head->the_next_nood = *head;
*head = the_new_head;
return (the_new_head);
}

/*_______________________________________________________________________*/

/**
 * appends_a_new_node_at_end - Appends a node to the tail of the list.
 * @head: Refers to the address of the pointer pointing to the head node
 * @string: Refers to the string field of a node.
 * @number: Refers to the index of a node utilized in the history
 *
 * Return: Refers to the size or number of elements in the list
 */
list_t *appends_a_new_node_at_end(list_t **head, const char *string, int number)
{
list_t *the_new_node, *node;

if (!head)
	return (NULL);

node = *head;
the_new_node = malloc(sizeof(list_t));
if (!the_new_node)
	return (NULL);
underscore_memset((void *)the_new_node, 0, sizeof(list_t));
the_new_node->number = number;
if (string)
{
	the_new_node->string = the_string_duplicates(string);
	if (!the_new_node->string)
	{
		free(the_new_node);
		return (NULL);
	}
}
if (node)
{
	while (node->the_next_nood)
		node = node->the_next_nood;
	node->the_next_nood = the_new_node;
}
else
	*head = the_new_node;
return (the_new_node);
}

/*_______________________________________________________________________*/

/**
 * prints_list_strings - Prints the string component of each element in
 * a list_t linked list.
 * @k: Pointer to the initial node.
 *
 * Return: Refers to the size or number of elements in the list
 */
size_t prints_list_strings(const list_t *k)
{
size_t x = 0;

while (k)
{
	the_string_prints_input(k->string ? k->string : "(nil)");
	the_string_prints_input("\n");
	k = k->the_next_nood;
	x++;
}
return (x);
}

/*_______________________________________________________________________*/

/**
 * deletes_node_at_specified_index - Deletes the node at the specified index.
 * @head: Refers to the address of the pointer pointing to the head node
 * @index: Specifies the index of the node to be deleted.
 *
 * Return: Returns 1 if the operation is successful, and 0 on failure.
 */
int deletes_node_at_specified_index(list_t **head, unsigned int index)
{
list_t *node, *is_prev_node;
unsigned int x = 0;

if (!head || !*head)
	return (0);

if (!index)
{
	node = *head;
	*head = (*head)->the_next_nood;
	free(node->string);
	free(node);
	return (1);
}
node = *head;
while (node)
{
	if (x == index)
	{
		is_prev_node->the_next_nood = node->the_next_nood;
		free(node->string);
		free(node);
		return (1);
	}
	x++;
	is_prev_node = node;
	node = node->the_next_nood;
}
return (0);
}

/*_______________________________________________________________________*/

/**
 * frees_memory_allocated_for_linked_list - Frees all nodes within a
 * linked list.
 * @is_part_head: Refers to the address of the pointer pointing to
 * the head node
 *
 * Return: This function has a `void` return type, indicating that it
 * does not return a value.
 */
void frees_memory_allocated_for_linked_list(list_t **is_part_head)
{
list_t *node, *node_next, *head;

if (!is_part_head || !*is_part_head)
	return;
head = *is_part_head;
node = head;
while (node)
{
	node_next = node->the_next_nood;
	free(node->string);
	free(node);
	node = node_next;
}
*is_part_head = NULL;
}

/*_______________________________________________________________________*/
