#include "shell.h"

/**
 * remove_comments - Removes comments from a command
 * @command: Command to process
 */

void remove_comments(char *command)
{
	char *comment_ptr;

	comment_ptr = strchr(command, '#');
	if (comment_ptr != NULL)
		*comment_ptr = '\0';
}
