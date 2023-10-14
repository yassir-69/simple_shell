#include "000-shell.h"

/*______________________________________________________________________*/

/**
 * cmd_check - checks if a file is an executable command
 * @info: the information structure
 * @pathway: file's pathway
 *
 * Return: Return 1 if it's true, otherwise 0.
 */
int cmd_check(info_t *info, char *pathway)
{
struct stat st;

(void)info;
if (!pathway || stat(pathway, &st))
	return (0);

if (st.st_mode & S_IFREG)
{
	return (1);
}
return (0);
}

/*______________________________________________________________________*/

/**
 * duplicate_characters - replicates characters or duplicates characters
 * @pathway_string: the PATH variable or string
 * @initiate: initial index or starting index
 * @halt: end index or stopping index
 *
 * Return: Return: pointer to the fresh buffer
 */
char *duplicate_characters(char *pathway_string, int initiate, int halt)
{
static char buf[1024];
int x = 0, v = 0;

for (v = 0, x = initiate; x < halt; x++)
	if (pathway_string[x] != ':')
		buf[v++] = pathway_string[x];
buf[v] = 0;
return (buf);
}

/*______________________________________________________________________*/

/**
 * locate_route - locates this command in the PATH variable
 * @info: the information structure
 * @pathway_string: the PATH variable or string
 * @cmd: the cmd to find
 *
 * Return: complete pathway of the command if found, or NULL
 */
char *locate_route(info_t *info, char *pathway_string, char *cmd)
{
int x = 0, current_position = 0;
char *pathway;

if (!pathway_string)
	return (NULL);
if ((string_llen(cmd) > 2) && begins_with(cmd, "./"))
{
	if (cmd_check(info, cmd))
		return (cmd);
}
while (1)
{
	if (!pathway_string[x] || pathway_string[x] == ':')
	{
	pathway = duplicate_characters(pathway_string, current_position, x);
		if (!*pathway)
			string_ccat(pathway, cmd);
		else
		{
			string_ccat(pathway, "/");
			string_ccat(pathway, cmd);
		}
		if (cmd_check(info, pathway))
			return (pathway);
		if (!pathway_string[x])
			break;
		current_position = x;
	}
	x++;
}
return (NULL);
}

/*______________________________________________________________________*/
