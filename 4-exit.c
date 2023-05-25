#include <stdlib.h>
#include "shell.h"

/**
 * exit_shell - Exit the shell
 */

void exit_shell(void)
{
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	(void)env;

	exit_shell();

	return (0);
}

